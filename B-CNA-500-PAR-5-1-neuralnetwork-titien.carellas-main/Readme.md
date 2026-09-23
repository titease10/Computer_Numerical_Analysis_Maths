# Neural Network Project

## Overview
This project is a Python implementation of a neural network designed to predict chess positions (checkmate scenarios). It utilizes a custom-built neural network and is capable of training on input data, predicting outcomes, and saving/loading models.

## Files in the Project
- `neural_network.py`: Contains the `NeuralNetwork` class with methods for the neural network's operations.
- `utils.py`: Includes utility functions used across the project.
- `main.py`: The main script that executes neural network operations based on command-line arguments.

## Requirements
- Python 3.x
- NumPy
- tqdm (optional, for progress bars)

Ensure you have the above requirements installed. You can install them using pip:
```
pip install numpy tqdm
```


## Usage
Run the `main.py` file with appropriate command-line arguments. Here are the available options:

- `--new`: Create a new neural network with specified layers. Example: `--new 64 32 5`
- `--load`: Load neural network from a file. Example: `--load filename.conf`
- `--train`: Train the neural network.
- `--predict`: Predict using the neural network.
- `--save`: Save the neural network state to a file. Example: `--save filename.conf`
- `file`: Specify the file containing data for training or prediction.

### Examples:
1. Train a new neural network and save the model:

    ```
    python main.py --new 64 32 5 --train --save model.conf
    ```
   
2. Load a neural network from a file and predict using it:

    ```
    python main.py --load model.conf --predict file.txt
    ```
3. Load a neural network from a file, train it, and save the model:

    ```
    python main.py --load model.conf --train --save model.conf
    ```

## Data Format
The data for training and prediction is stored in text files. Each line in the file represents a single data point. The data point is a list of numbers separated by spaces. The first number is the input value and the second number is the output value. The input value is a 64-bit integer representing a chess position. The output value is a 5-bit integer representing the outcome of the position. The 5 bits represent the following outcomes:
- 0: White wins
- 1: Black wins
- 1/2: Draw