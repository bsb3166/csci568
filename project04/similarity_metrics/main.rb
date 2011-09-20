#!/usr/bin/env ruby

require_relative 'movies'
require_relative 'movie_utils'

ratingset = generate_ratingset(PEOPLE, MOVIES, POSSIBLE_RATINGS)

#print_ratings(ratingset)

sample_ratings = generate_ratingset(['john'], MOVIES, POSSIBLE_RATINGS)

#print_ratings(johns_ratings)

puts "--------------^_^------------------"
puts "(1)EuclideanSimilarity:"
ratingset.each do |key, value|
  puts "#{key}: #{euclideanSimilarity(value, sample_ratings['john'])}"
end
puts "--------------^_^------------------"

puts "CosineSimilarity:"
ratingset.each do |key, value|
  puts "#{key}: #{cosineSimilarity(value, sample_ratings['john'])}"
end
puts "--------------^_^------------------" 

puts "PearsonCorrelationCoeff:"
ratingset.each do |key, value|
  puts "#{key}: #{pearsonCorrelationCoeff(value, sample_ratings['john'])}"
end
puts "--------------^_^------------------"

binaryset = generate_binaryset(ratingset, MOVIES)

#print_binary(binaryset)

sample_binary = generate_binaryset(sample_ratings, MOVIES)

#print_ratings(johns_ratings)

puts "SMC:"
binaryset.each do |key, value|
  puts "#{key}: #{smc(value, sample_binary['john'])}"
end
puts "--------------^_^------------------"

puts "JaccardSimilarity:"
binaryset.each do |key, value|
  puts "#{key}: #{jaccardSimilarity(value, sample_binary['john'])}"
end
puts "--------------^_^------------------"
puts "--------------END------------------"

