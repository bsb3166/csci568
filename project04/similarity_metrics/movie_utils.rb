def print_ratings(ratingset)
  ratingset.each do |person, ratings|
    puts person
    ratings.each do |flick, rating|
      puts "\t#{rating} #{flick}"
    end
  end
end

def generate_ratingset(people, movies, possible_ratings)
  {}.tap do |ratingset|
    people.each do |person|
      ratingset[person] = {}.tap do |ratings|
        movies.sort_by{ rand }.slice(0..VIEWINGS).each do |flick|
          ratings[flick] = possible_ratings[rand(possible_ratings.size)]
        end
      end
    end
  end
end

def euclideanSimilarity(a, b)
  euclideanSimilarity = 1/euclideanDistance(a, b)
end

def euclideanDistance(a, b)
  common_film_names = a.keys & b.keys
  if common_film_names.empty?
    return Infinity
  end
  euclideanDistance = 0.0
  common_film_names.each do |film_name|
    a_rating = a[film_name]
    b_rating = b[film_name]
    difference_squared = (a_rating - b_rating)**2
    euclideanDistance += difference_squared
  end
  euclideanDistance = Math.sqrt(euclideanDistance)
end

def cosineSimilarity(a,b)
  common_film_names = a.keys & b.keys
  if common_film_names.empty?
    return 0
  end
  cosineSimilarity = 0.0
  a_dot_b = 0.0
  a_norm = 0.0
  b_norm = 0.0
  common_film_names.each do |film_name|
    a_rating = a[film_name]
    b_rating = b[film_name]
    a_dot_b += (a_rating * b_rating)
    a_norm += a_rating**2
    b_norm += b_rating**2
  end
  a_norm = Math.sqrt(a_norm)
  b_norm = Math.sqrt(b_norm)
  cosineSimilarity = a_dot_b / (a_norm * b_norm)
end
