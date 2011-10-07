#!/usr/bin/env ruby

class Person
  def initialize()
    @data = Hash.new { |hash, key| hash[key] = [] }
  end
  def [](key)
    @data[key]
  end
  def []=(key,words)
    @data[key] += [words].flatten
    @data[key].uniq!
  end
end

people = Array.new
winorlos = Person.new
#d = Person.new
#d['chong'] = %w(chong ding +)
#puts d['chong']

counter = 1

begin
    file = File.new("winners_losers.csv", "r")
    while (line = file.gets)
        #puts "#{counter}: #{line}"
		array = line.split(', ')
		fullname = array[0]
		people.push(fullname)
		split_full_name = fullname.split(' ')
		#puts split_full_name
        if split_full_name.length == 2
		  firstname = split_full_name[0]
		  middlename = nil
		  lastname = split_full_name[1]
		elsif split_full_name.length == 3
		  firstname = split_full_name[0]
		  middlename = split_full_name[1]
		  lastname = split_full_name[2]		
		end
        counter = counter + 1
        winorlos[fullname] = [firstname, middlename, lastname, array[1]];
    end
    file.close
    rescue => err
    puts "Exception: #{err}"
    err
end

a = "cruel world"
a.scan(/\w+/)        #=> ["cruel", "world"]

#winorlos.each do |fullname, firstname, middlename, lastname, status|
#  puts "\t#{fullname} #{firstname} #{middlename} #{lastname} #{status}"
#end
outputfile = File.new("gen_attribute","w")
outputfile.puts "Name 1st 2nd 3rd 4th 5th #ofFullName #ofFirstName #ofLastName RatioofFirstName RatioofLastName MI.? FirstName<LastName? '-'inFirstName? '-'inLastName?"
people.each do |itself|
#  puts winorlos[itself]
#  puts winorlos[itself][3]
 
# Name 1st 2nd 3rd 4th 5th #ofFullName #ofFirstName #ofLastName RatioofFirstName RatioofLastName MI.? FirstName<LastName? '-'inFirstName? '-'inLastName?
# object attribute0 attribute1 attribute2 attribute3 attribute4 attribute5 attribute6 attribute7
  if winorlos[itself][1].nil?
    lengthoffullname = winorlos[itself][0].length+winorlos[itself][2].length
  else
    lengthoffullname = winorlos[itself][0].length+winorlos[itself][1].length+winorlos[itself][2].length
  end  
  lengthoffirstname = winorlos[itself][0].length
  #puts winorlos[itself][1]
  if winorlos[itself][1].nil?
    lengthofmiddlename = 0
  else
    lengthofmiddlename = winorlos[itself][1].length
  end   
  lengthoflastname = winorlos[itself][2].length
  ratioofFirstName = lengthoffirstname.to_f/lengthoffullname.to_f
  ratioofLastName = lengthoflastname.to_f/lengthoffullname.to_f
  if lengthofmiddlename==0
    attribute5 = 0
  else
    attribute5 = 1
  end
  if lengthoffirstname<lengthoflastname
    attribute6 = 0
  else
    attribute6 = 1
  end
  if winorlos[itself][0].include? "-"
    attribute7 = 1
  else
    attribute7 = 0
  end  
  if winorlos[itself][2].include? "-"
    attribute8 = 1
  else
    attribute8 = 0
  end  
#  outputfile.puts "#{itself} #{lengthoffullname} #{lengthoffirstname} #{lengthoflastname} #{ratioofFirstName} #{ratioofLastName} #{attribute5} #{attribute6} #{attribute7} #{attribute8}"
#  printf(outputfile,"%25s %3d %3d %3d %3.2f %3.2f %1d %1d %1d %1d\n",itself,lengthoffullname,lengthoffirstname,lengthoflastname,ratioofFirstName,ratioofLastName,attribute5,attribute6,attribute7,attribute8) 
#  printf(outputfile,"%3d %3d %3d %3.2f %3.2f %1d %1d %1d %1d\n",lengthoffullname,lengthoffirstname,lengthoflastname,ratioofFirstName,ratioofLastName,attribute5,attribute6,attribute7,attribute8)   
#  printf(outputfile,"%s,%d,%d,%d,%f,%f,%d,%d,%d,%d,%s",winorlos[itself][2],lengthoffullname,lengthoffirstname,lengthoflastname,ratioofFirstName,ratioofLastName,attribute5,attribute6,attribute7,attribute8,winorlos[itself][3]) 
#   printf(outputfile,"%s\n",itself[3])
printf(outputfile,"%s,%s,%s,%s,%s,%s,%d,%d,%d,%f,%f,%d,%d,%d,%d,%s",itself,itself[0],itself[1],itself[2],itself[3],itself[4],lengthoffullname,lengthoffirstname,lengthoflastname,ratioofFirstName,ratioofLastName,attribute5,attribute6,attribute7,attribute8,winorlos[itself][3]) 
end

outputfile.close


#puts "Hello,How,Are,You,Today".split(',').join('.')