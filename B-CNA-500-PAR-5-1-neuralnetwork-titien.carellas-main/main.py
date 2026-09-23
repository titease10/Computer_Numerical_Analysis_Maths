import argparse
import numpy as np
import pickle
from neural_network import NeuralNetwork
import utils
from tqdm import tqdm
#neural config we use : 64 32 5

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
            input_vector = utils.fen_to_input(fen)
            input_array = np.array(input_vector)
            training_data.append((input_array, checkmate))

    return training_data

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
        prediction_data = utils.load_data_for_prediction(args.file)
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
