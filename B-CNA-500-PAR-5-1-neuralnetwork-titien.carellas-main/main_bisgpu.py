import argparse
import cupy as np
import pickle

from tqdm import tqdm
#neural config we use : 64 32 5

def sigmoid(x):
    x_clipped = np.clip(x, -500, 500)
    if np.any(x != x_clipped):
        print(f"Clipped input from {x} to {x_clipped}")
    return 1 / (1 + np.exp(-x_clipped))

def normalize_data(data):
    mean = np.mean(data, axis=0)
    std = np.std(data, axis=0)
    return (data - mean) / std
def clip_gradients(gradients, max_value):
    for i in range(len(gradients)):
        np.clip(gradients[i], -max_value, max_value, out=gradients[i])
    return gradients
def parse_args():
    parser = argparse.ArgumentParser(description='My Torch Neural Network CLI')
    parser.add_argument('--new', nargs='+', type=int, help='Create a new neural network with specified layers')
    parser.add_argument('--load', type=str, help='Load neural network from file')
    parser.add_argument('--train', action='store_true', help='Train the neural network')
    parser.add_argument('--predict', action='store_true', help='Predict using the neural network')
    parser.add_argument('--save', type=str, help='Save neural network state to file')
    parser.add_argument('file', type=str, nargs='?', help='File containing data')
    return parser.parse_args()

def parse_training_data(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    training_data = []
    checkmate = 0
    for line in lines:
        if line.startswith('CHECKMATE'):
            checkmate = 1 if 'True' in line else 0
        elif line.startswith('FEN'):
            fen = line.split(':')[1].strip()
            input_vector = fen_to_input(fen)
            input_array = np.array(input_vector)
            training_data.append((input_array, checkmate))

    return training_data

def fen_to_input(fen):
    piece_to_num = {'p': -1 / 6, 'r': -2 / 6, 'n': -3 / 6, 'b': -4 / 6, 'q': -5 / 6, 'k': -6 / 6,
                    'P': 1 / 6, 'R': 2 / 6, 'N': 3 / 6, 'B': 4 / 6, 'Q': 5 / 6, 'K': 6 / 6}
    input_vector = []
    rows = fen.split(' ')[0].split('/')
    for row in rows:
        for char in row:
            if char.isdigit():
                input_vector.extend([0] * int(char))  # Ajout de cases vides
            else:
                input_vector.append(piece_to_num[char])  # Ajout de la pièce
    return input_vector
def load_data_for_prediction(filename):
    with open(filename, 'r') as file:
        fen_positions = file.readlines()
    return [fen_to_input(fen.strip()) for fen in fen_positions]

def relu(x):
    return np.maximum(0, x)
def relu_derivative(x):
    return np.where(x > 0, 1.0, 0.0)
class NeuralNetwork:
    def __init__(self, layers):
        np.random.seed(0)
        self.layers = layers
        self.weights = [np.random.rand(layers[i], layers[i + 1]) for i in range(len(layers) - 1)]
        # Initialize batch normalization parameters
        self.gamma = [np.ones((1, layers[i + 1])) for i in range(len(layers) - 1)]
        self.beta = [np.zeros((1, layers[i + 1])) for i in range(len(layers) - 1)]
        self.moving_mean = [np.zeros((1, layers[i + 1])) for i in range(len(layers) - 1)]
        self.moving_variance = [np.zeros((1, layers[i + 1])) for i in range(len(layers) - 1)]
        self.momentum = 0.9  # A common choice for moving average momentum
        self.biases = [np.zeros((1, layers[i + 1])) for i in range(len(layers) - 1)]
        print("Initialized Neural Network with layers:", self.layers)

    def batch_normalize(self, activations, layer_index, is_training):
        gamma = self.gamma[layer_index]
        beta = self.beta[layer_index]
        epsilon = 1e-5

        if is_training:
            # Compute batch statistics
            mean = np.mean(activations, axis=0, keepdims=True)
            variance = np.var(activations, axis=0, keepdims=True)
            # Update moving averages
            self.moving_mean[layer_index] = self.momentum * self.moving_mean[layer_index] + (1 - self.momentum) * mean
            self.moving_variance[layer_index] = self.momentum * self.moving_variance[layer_index] + (
                        1 - self.momentum) * variance
        else:
            # Use moving averages during inference
            mean = self.moving_mean[layer_index]
            variance = self.moving_variance[layer_index]

        activations_normalized = (activations - mean) / np.sqrt(variance + epsilon)
        return gamma * activations_normalized + beta

    def forward_propagate(self, input_data, is_training=True):
        activations = [input_data]
        for i, weight in enumerate(self.weights):
            net_input = np.dot(activations[-1], weight)

            # Apply batch normalization before the activation function
            if i < len(self.weights) - 1:
                net_input = self.batch_normalize(net_input, i, is_training)

            # Apply activation function
            activation = relu(net_input) if i < len(self.weights) - 1 else sigmoid(net_input)
            activations.append(activation)

        return activations
    @staticmethod
    def sigmoid_derivative(x):
        return x * (1 - x)
    def calculate_error(self, predicted_output, expected_output):
        return (expected_output - predicted_output) * self.sigmoid_derivative(predicted_output)

    def backpropagate(self, error, activations):
        gradients = []

        for i in range(len(self.weights) - 1, -1, -1):
            current_activations = activations[i + 1]
            if i != len(self.weights) - 1:
                error = np.dot(gradients[0], self.weights[i + 1].T)
            current_error = error
            derivative_func = relu_derivative if i < len(self.weights) - 1 else self.sigmoid_derivative
            current_gradients = current_error * derivative_func(current_activations)
            gradients.insert(0, current_gradients)

        return gradients


    def update_gradients(self, gradients, activations):
        for i in range(len(self.weights)):
            self.weights[i] += np.dot(activations[i].T, gradients[i])

    def update_weights(self, gradients, learning_rate):
        for i, weight in enumerate(self.weights):
            old_weight = weight.copy()
            weight -= learning_rate * gradients[i]
            # Update gamma and beta if i < len(self.weights) - 1
            # Compute gradients for gamma and beta and update them
            if i < len(self.weights) - 1:
                gamma_gradient = np.sum(gradients[i], axis=0, keepdims=True)
                self.gamma[i] -= learning_rate * gamma_gradient
                beta_gradient = np.sum(gradients[i], axis=0, keepdims=True)
                self.beta[i] -= learning_rate * beta_gradient


    from concurrent.futures import ThreadPoolExecutor
    def train(self, inputs, expected_outputs, epochs, learning_rate):
        total_iterations = epochs * len(inputs)
        loss_history = []

        for epoch in range(epochs):
            epoch_loss = 0
            with tqdm(total=len(inputs), desc=f"Epoch {epoch+1}/{epochs}") as pbar:
                for input, expected in zip(inputs, expected_outputs):
                    # Forward propagation
                    activations = self.forward_propagate(input)

                    # Calculate error
                    error = self.calculate_error(activations[-1], expected)
                    epoch_loss += np.sum(error ** 2)  # Sum of squared errors

                    # Backpropagation and weight update
                    gradients = self.backpropagate(error, activations)
                    self.update_weights(gradients, learning_rate)

                    pbar.update(1)  # Update the progress bar by 1

            average_loss = epoch_loss / len(inputs)
            loss_history.append(epoch_loss)
            print(f"Average Loss: {average_loss} epoch loss: {epoch_loss}")
    def predict_forward_propagate(self, X):
        activations = [X]
        for i in range(len(self.weights)):
            Z = np.dot(activations[-1], self.weights[i]) + self.biases[i]
            activation = relu(Z) if i < len(self.weights) - 1 else sigmoid(Z)
            activations.append(activation)
        return activations
    def predict_checkmate(self, input_data):
        final_activations = self.predict_forward_propagate(input_data)

        prediction = final_activations[-1]
        if np.any(prediction > 0.65):
            print("Checkmate found!")
        else:
            print("No checkmate.")
        return prediction


    def save(self, filename):
        with open(filename, 'wb') as f:
            pickle.dump({
                'layers': self.layers,
                'weights': [w.tolist() for w in self.weights],
                # Convertir les tableaux numpy en listes pour une meilleure compatibilité
            }, f)

    #@staticmethod
    def load(filename):
        with open(filename, 'rb') as f:
            data = pickle.load(f)
            print("Loaded Neural Network with layers:", data['layers'])
            nn = NeuralNetwork(data['layers'])
            nn.weights = [np.array(w) for w in data['weights']]  # Convertir les listes en tableaux numpy
            return nn

    def evaluate(self, inputs, expected_outputs):
        predictions = [self.predict(input) for input in inputs]
        accuracy = sum(int(pred == exp) for pred, exp in zip(predictions, expected_outputs)) / len(inputs)
        return accuracy

    def predict(self, input_data):
        final_activations = self.forward_propagate(input_data)
        return final_activations[-1]


def main():
    args = parse_args()

    if args.new:
        np.random.seed(0)
        nn = NeuralNetwork(args.new)
        debug_data = np.random.normal(size=(1, args.new[0]))
        debug_activations = nn.forward_propagate(debug_data)
        for i, activation in enumerate(debug_activations):
            print(f"Initial activation at layer {i}: {activation}")
    elif args.load:
        nn = NeuralNetwork.load(args.load)
    else:
        raise ValueError("No neural network specified")

    if args.train:
        training_data = parse_training_data(args.file)
        inputs = [data[0] for data in training_data] # matix of 64

        outputs = [data[1] for data in training_data] # 1 for checkmate 0 for not
        nn.train(inputs, outputs, 50, 0.05)

    if args.predict:
        prediction_data = load_data_for_prediction(args.file)
        for data in prediction_data:
            is_checkmate = nn.predict_checkmate(data)
            print(f"Checkmate: {is_checkmate}")

            # Flatten the array for easy iteration if it's multi-dimensional
            predictions_flat = np.array(is_checkmate).flatten()

            # Find the values closest to 0 and 1
            closest_to_zero = min(predictions_flat, key=lambda x: abs(x - 0))
            closest_to_one = min(predictions_flat, key=lambda x: abs(x - 1))

            print(f"Average for this position: {np.average(predictions_flat)}")
            print(f"Value closest to 0: {closest_to_zero}")
            print(f"Value closest to 1: {closest_to_one}")


    if args.save:
        nn.save(args.save)

if __name__ == "__main__":
    main()
