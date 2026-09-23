import numpy as np

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
