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

def pearsonCorrelationCoeff(a,b)
  common_film_names = a.keys & b.keys
  if common_film_names.empty?
    return 0
  end
  
  sum_a = 0
  sum_b = 0
  square_sum1 = 0
  square_sum2 = 0
  product = 0
  numerator = 0
  denominator = 0
  result = 0
  n = common_film_names.length
  
  common_film_names.each do |film_name| 
    # Summation over all attributes for both objects
    sum_a += a[film_name]
  	sum_b += b[film_name]
    # Sum the squares
  	square_sum1 += a[film_name]**2
  	square_sum2 += b[film_name]**2
    # Add up the products
  	product += a[film_name] * b[film_name]
  end

  #Calculate Pearson Correlation score
  numerator = product - (sum_a*sum_b/n)
  denominator = Math.sqrt((square_sum1 - (sum_a**2)/n) * (square_sum2 - (sum_b**2)/n))
      
  # Can"t have division by 0
  if denominator == 0
      return 0
  end
  
  result = numerator/denominator
  return result
end

def print_binary(binaryset)
  binaryset.each do |person, binary|
    puts person
    binary.each do |flick, match|
      puts "\t#{match} #{flick}"
    end
  end
end


def generate_binaryset(ratingset, movies)
  {}.tap do |binaryset|
    ratingset.each do |person, ratings|
      binaryset[person] = {}.tap do |binary|
        movies.each do |film_name|
          binary[film_name] = ratings.has_key?(film_name)
        end
      end
    end
  end
end

def smc(a,b)

  numerator = 0.0
  denominator = a.length
  smc = 0.0
  
  a.each do |flick, match|
  	if  a[flick] == b[flick] 
  	  numerator += 1
    end
  end 
  smc =  numerator/denominator  
end


def jaccardSimilarity(a,b)

  numerator = 0.0
  denominator = a.length
  jaccardSimilarity = 0.0
 
  a.each do |flick, match|
  	if  a[flick] && b[flick]
  	  numerator += 1
    elsif  !a[flick] && !b[flick]
  	  denominator -= 1
    end 
  end 
  jaccardSimilarity =  numerator/denominator  
end

