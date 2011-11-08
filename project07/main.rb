require_relative 'ann'
layers = [3,2,3]
inputs = [1.0, 0.25, -0.5]
ideal_outputs = [1.0, -1.0, 0.0]
ann = Ann.new(layers)
ann.train(inputs, ideal_outputs)