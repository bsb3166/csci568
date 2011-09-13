/*
 #myrandomnumber Tutorial
 blprnt@blprnt.com
 April, 2010
 */

//This is the Google spreadsheet manager and the id of the spreadsheet that we want to populate, along with our Google username & password
SimpleSpreadsheetManager sm;
String sUrl = "t6mq_WLV5c5uj6mUNSryBIA";
String googleUser = GUSER;
String googlePass = GPASS;

//This is the font object
PFont label;
  
void setup() {
    //This code happens once, right when our sketch is launched
    size(800,800);
    background(0);
    smooth();

    //Ask for the list of numbers
    int[] numbers = getNumbers();
    
    
    //draw
/*    
    fill(255,40);
    noStroke();
    for (int i =0; i < numbers.length; i++) {
      ellipse(numbers[i] * 8, height/2, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 10, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 20, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 30, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 40, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 50, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 60, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 70, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 80, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 90, 8, 8);
    }
    //A line of random numbers
    for (int i =0; i < numbers.length; i++) {
      ellipse(ceil(random(0,99)) * 8, height/2 + 100, 8, 8);
    }
*/

/*
   barGraph(numbers, 400);
   
   for (int i =1; i < 7; i++) {
     int[] randoms = getRandomNumbers(255);
     barGraph(randoms, 100 + (i * 130));
   }
*/

  
  label = createFont("Helvetica", 24);
  colorGridLabel(numbers, 50, 50, 70);
  //colorGrid(numbers, 50, 50, 70);

}

void barGraph( int[] nums, float y ) {
  // Make a list of number counts
  int[] counts = new int[100];
  //Fill it with zeros
  for (int i=1; i<100; i++) {
    counts[i] = 0;
  }
  //Tally the counts
  for (int i=1; i< nums.length; i++) {
    counts[nums[i]] ++;
  }
  
 //Draw the bar graph
 for (int i = 0; i < counts.length; i++) {
   colorMode(HSB);
   fill(counts[i] * 30, 255, 255);
   //fill(255, counts[i] * 30, 0);
   rect(i * 8, y, 8, -counts[i] * 10);
 }  
}


void colorGrid(int[] nums, float x, float y, float s) {
 //Make a list of number counts
 int[] counts = new int[100];
 //Fill it with zeros
 for (int i = 0; i < 100; i++) {
   counts[i] = 0;
 }
 //Tally the counts
 for (int i = 0; i < nums.length; i++) {
   counts[nums[i]] ++;
 }
 
 pushMatrix();
 translate(x,y);
 //Draw the grid
 for (int i = 0; i < counts.length; i++) {
   colorMode(HSB);
   fill(counts[i] * 30, 255, 255, counts[i] * 30);
   rect((i%10)*s,floor(i/10)*s, s, s);
   
  
 }
 popMatrix();
}

void colorGridLabel(int[] nums, float x, float y, float s) {
 //Make a list of number counts
 int[] counts = new int[100];
 //Fill it with zeros
 for (int i = 0; i < 100; i++) {
   counts[i] = 0;
 }
 //Tally the counts
 for (int i = 0; i < nums.length; i++) {
   counts[nums[i]] ++;
 }
 
 pushMatrix();
 translate(x,y);
 //Draw the grid
 for (int i = 0; i < counts.length; i++) {
   colorMode(HSB);
   fill(counts[i] * 30, 255, 255, counts[i] * 30);
   textAlign(CENTER);
   textFont(label);
   textSize(s/2);
   text(i, (i % 10) * s + 30 , floor(i/10) * s + 50);
   rect((i%10)*s,floor(i/10)*s, s, s);
   
  
 }
 popMatrix();
}


void draw() {
  //This code happens once every frame.
}

