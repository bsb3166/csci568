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

