class Ann
  attr_reader :input, :output, :hidden_output, :ideal_output, :layers

    def initialize(number_of_layers)
      # initialze arrays
      @N = 0.1
      @layers = Array.new
      @input = Array.new
      @current_output = Array.new
      @hidden_output = Array.new
	  number_of_layers.each_index do |i|
		layer = Layer.new
		(0...number_of_layers[i]).each do |n|
			if i != number_of_layers.size() - 1
				layer.add_neuron(Neuron.new(number_of_layers[i+1]))
			else
				layer.add_neuron(Neuron.new(0))
			end
		end
		@layers.push(layer)
	  end	  
	end
		
	def forward_phase
		@hidden_output = Array.new(layers[1].neurons.size(), 0.0)
		@hidden_output.each_index do |k|
			@converged_output = Array.new(layers[1].neurons.size, 0.0)
			total = 0.0
			@input.each_index do |i|
				total += @input[i] * layers[0].neurons[i].weights[k]
			end
			@hidden_output[k] = total
		end
		@current_output = Array.new(@ideal_output.size, 0.0)
		@current_output.each_index do |j|
			total = 0.0
			@hidden_output.each_index do |k|
				total += @hidden_output[k] * layers[1].neurons[k].weights[j]
			end
			@current_output[j] = total
		end
		@current_output
	end

	# backward_phase of backpropogation
	def backward_phase
		deltas_of_output = Array.new(@current_output.size, 0.0)
		
		@current_output.each_index do |i|
		  error = @ideal_output[i] - @current_output[i]
		  deltas_of_output[i] = dtanh(@current_output[i]) * error
		end
		
		deltas_of_hidden_layers = Array.new(@hidden_output.size, 0.0)

		deltas_of_hidden_layers.each_index do |k|
		  error = 0.0
		  deltas_of_output.each_index do |j|
			error += deltas_of_output[j] * layers[1].neurons[k].weights[j]
		  end
			deltas_of_hidden_layers[k] = dtanh(@hidden_output[k]) * error
		end

		@hidden_output.each_index do |k|
			@current_output.each_index do |j|
				diff = deltas_of_output[j] * @hidden_output[k]
				layers[1].neurons[k].weights[j] += diff * @N
			end
		end

		@input.each_index do |i|
		  @hidden_output.each_index do |j|
			diff = deltas_of_hidden_layers[j] * @input[i]
			layers[0].neurons[i].weights[j] += diff * @N
		  end
		end
	end

	def train(input, output)
      @input = input	
	  @ideal_output = output		
	  converged_output = @input
	  err0 = 1
	  err1 = 1
	  err2 = 1
	  while err0 > 0.00000000001 and err1 > 0.00000000001 and err2 > 0.00000000001
          converged_output = forward_phase
		  backward_phase
          err0 = (@ideal_output[0] - @current_output[0]).abs
		  err1 = (@ideal_output[1] - @current_output[1]).abs
		  err2 = (@ideal_output[2] - @current_output[2]).abs
	  end
      puts "Converged Output:"
	  puts "Output[0]: " + converged_output[0].to_s
	  puts "Output[1]: " + converged_output[1].to_s
	  puts "Output[2]: " + converged_output[2].to_s
	end

	def dtanh(y)
		1.0
	end	

end

class Neuron
	attr_accessor :weights
	def initialize(numWeights)
		@weights = Array.new(numWeights)
		@weights.each_index do |i|
			@weights[i] = -1 + rand(100)/50.0
		end
	end
end

class Layer
	attr_accessor :neurons
	def initialize
	  @neurons = Array.new
	end

	def add_neuron(neuron)
	  @neurons.push(neuron)
	end

end
