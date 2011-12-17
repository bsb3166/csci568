#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <cctype> 
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <set>
#include <math.h>

using namespace std;

typedef struct{
  string id;
  int score;
  int ideal_score;
  float confidence;
}item;

typedef struct{
  string id;
  int numItems;
  vector<item> items;
}user;

typedef struct{
	string trackId;
	string albumId;
	string artistId;
	vector<string> genres;  
}track;

typedef struct{
	string albumId;
  string artistId;
  vector<string> genres;    
}album;

typedef struct{
	album  ialbum;
	string iartist;
	track  itrack;
	string igenre;
	string type;
}itemType;

// global variables
vector<string> genres;
vector<string> artists;
vector<album> albums;
vector<track> tracks;
vector<user> users;
vector<user> users_validation;
vector<user> users_test;

bool increment_genre (string i,string j) { return (i<j); }
bool decrement_genre (string i,string j) { return (i>j); }
bool increment_item  (item   i,item   j) { return (atoi(i.id.c_str())<atoi(j.id.c_str())); }
bool decrement_item  (item   i,item   j) { return (atoi(i.id.c_str())>atoi(j.id.c_str())); }

void StringSplit(const string &str, vector<string> &tokens, const string &delimiters = " ")
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void read_input(string dir)
{
	  string filename;
	  string line;
	  ifstream OpenFile;
	  vector<string> tokens;
	  int ix;	  
	  //read genreData
	  filename = dir + "genreData1.txt";
	  cout<<"Read genre data:    genreData1.txt"<<endl;
	  OpenFile.open(filename.c_str());
	  if (!OpenFile) cerr<<"error: unable to open input file: "<<filename<<endl;  	  
    while(!OpenFile.eof())
      { 
      	getline(OpenFile,line);
      	if(line.size()!=0) genres.push_back(line);      	
      } 
	  //cout<<"size = "<<genres.size()<<endl;
	  OpenFile.close();
	  OpenFile.clear();

	  //read albumData
	  filename = dir + "albumData1.txt";
	  cout<<"Read album data:    albumData1.txt"<<endl;
	  OpenFile.open(filename.c_str());
	  if (!OpenFile) cerr<<"error: unable to open input file: "<<filename<<endl; 
	  album single_album;
    while(!OpenFile.eof())
      { 
      	tokens.clear();
      	getline(OpenFile,line);     	
      	if(line.size()!=0) {   
      		 		
      	  StringSplit(line, tokens,"|");
      	  //cout<<tokens[0]<<endl;
      	  single_album.albumId = tokens[0];
      	  single_album.artistId = tokens[1];
      	  single_album.genres.clear();
          for(ix=0+2;ix!=tokens.size();ix++)
      	    single_album.genres.push_back(tokens[ix]);
     	    //cout<<"size of generes= "<<single_album.genres.size()<<endl;
      	  albums.push_back(single_album);     	  
        } 
             	
      } 
	  //cout<<"size = "<<albums.size()<<endl;
	  //cout<<"size = "<<genres.size()<<endl;
	  OpenFile.close();
	  OpenFile.clear();
	  	  	  
	  //read artistData
	  filename = dir + "artistData1.txt";
	  cout<<"Read artist data:   artistData1.txt"<<endl;
	  OpenFile.open(filename.c_str());
	  if (!OpenFile) cerr<<"error: unable to open input file: "<<filename<<endl;  	  
    while(!OpenFile.eof())
      { 
      	getline(OpenFile,line);
      	if(line.size()!=0) artists.push_back(line);      	
      } 
	  //cout<<"size = "<<artists.size()<<endl;
	  OpenFile.close();
	  OpenFile.clear();	 
	   
	  //read trackData
	  filename = dir + "trackData1.txt";
	  cout<<"Read track data:    trackData1.txt"<<endl;
	  OpenFile.open(filename.c_str());
	  if (!OpenFile) cerr<<"error: unable to open input file: "<<filename<<endl; 
	  track single_track;
    while(!OpenFile.eof())
      { 
      	tokens.clear();
      	getline(OpenFile,line);     	
      	if(line.size()!=0) {   
      		 		
      	  StringSplit(line, tokens,"|");
      	  //cout<<tokens[0]<<endl;
      	  single_track.trackId = tokens[0];
      	  single_track.albumId = tokens[1];
      	  single_track.artistId = tokens[2];
      	  single_track.genres.clear();
          for(ix=0+3;ix!=tokens.size();ix++)
      	    single_track.genres.push_back(tokens[ix]);
      	  sort(single_track.genres.begin(),single_track.genres.end(),increment_genre);  
     	    //cout<<"size of generes= "<<single_track.genres.size()<<endl;
      	  tracks.push_back(single_track);     	  
        } 
             	
      } 
	  //cout<<"size = "<<tracks.size()<<endl;
	  OpenFile.close();
	  OpenFile.clear();	
	  
	    
	  //read trainData
	  filename = dir + "trainIdx1.firstLines.txt";
	  cout<<"Read training data: trainIdx1.firstLines.txt"<<endl;
	  OpenFile.open(filename.c_str());
	  if (!OpenFile) cerr<<"error: unable to open input file: "<<filename<<endl; 
	  user single_user;
    while(!OpenFile.eof())
      { 
      	tokens.clear();
      	single_user.items.clear(); 
      	getline(OpenFile,line);     	
      	if(line.size()!=0) {   
      		if(line.find('|')) {
      			StringSplit(line, tokens,"|");
        	  single_user.id = tokens[0];
        	  single_user.numItems = atoi(tokens[1].c_str()); 
        	  item single_item; 
        	  for (ix=0;ix!=single_user.numItems;ix++) {
        	  	tokens.clear();
        	  	getline(OpenFile,line);     			
          	  StringSplit(line, tokens,"\t");
          	  single_item.id = tokens[0];
          	  single_item.score = atoi(tokens[1].c_str());
          	  single_item.ideal_score = atoi(tokens[1].c_str()); 
          	  single_item.confidence = 1.0;
          	  single_user.items.push_back(single_item); 
        	  }
        	  sort(single_user.items.begin(),single_user.items.end(),increment_item);
        	  users.push_back(single_user);  
        	  //cout<<single_user.id<<" and "<<single_user.numItems<<endl;       	  
      		}	   	  
        } 
             	
      } 
	  //cout<<"size = "<<users.size()<<endl;
	  OpenFile.close();
	  OpenFile.clear();		  
}

void read_validationUser(string dir)
{
	  string filename;
	  string line;
	  ifstream OpenFile;
	  vector<string> tokens;
	  int ix;	  
	  //read Validation Data
	  filename = dir + "validationIdx1.firstLines.txt";
	  //filename = dir + "test.txt";
	  cout<<"Read validation data: validationIdx1.firstLines.txt"<<endl;
	  OpenFile.open(filename.c_str());
	  if (!OpenFile) cerr<<"error: unable to open input file: "<<filename<<endl; 
	  user single_user;
    while(!OpenFile.eof())
      { 
      	tokens.clear();
      	single_user.items.clear(); 
      	getline(OpenFile,line);     	
      	if(line.size()!=0) {   
      		if(line.find('|')) {
      			StringSplit(line, tokens,"|");
        	  single_user.id = tokens[0];
        	  single_user.numItems = atoi(tokens[1].c_str()); 
        	  item single_item; 
        	  for (ix=0;ix!=single_user.numItems;ix++) {
        	  	tokens.clear();        	  	
        	  	getline(OpenFile,line);     			
          	  StringSplit(line, tokens,"\t");
          	  single_item.id = tokens[0];
          	  //cout<<tokens[0]<<endl; 
          	  single_item.ideal_score = atoi(tokens[1].c_str());
          	  single_item.score = -1; // score needs to be predicted
          	  single_item.confidence = 0.0; // confidence is 0 when initialized    
          	  //cout<<single_item.id<<endl;  	  
          	  single_user.items.push_back(single_item); 
        	  }
        	  
        	  //cout<<single_user.id<<"|"<<single_user.numItems<<endl;
        	  //cout<<single_user.items[0].id<<endl;  
        	  //cout<<single_user.items[1].id<<endl;  
        	  //cout<<single_user.items[2].id<<endl;  
        	  //cout<<single_user.items[3].id<<endl;  
        	  //cout<<endl; 
        	  
        	  // don't sort them because you want to print with the samw order with the input file
        	  //sort(single_user.items.begin(),single_user.items.end(),increment_item);
        	  users_validation.push_back(single_user);  
        	  //cout<<single_user.id<<" and "<<single_user.numItems<<endl;       	  
      		}	   	  
        } 
             	
      } 
	  //cout<<"size = "<<users.size()<<endl;
	  OpenFile.close();
	  OpenFile.clear();		
	  
}

void read_testUser(string dir)
{
	  string filename;
	  string line;
	  ifstream OpenFile;
	  vector<string> tokens;
	  int ix;	  
	  //read test Data
	  filename = dir + "testIdx1.firstLines.txt";
	  cout<<"Read test data: testIdx1.firstLines.txt"<<endl;
	  OpenFile.open(filename.c_str());
	  if (!OpenFile) cerr<<"error: unable to open input file: "<<filename<<endl; 
	  user single_user;
    while(!OpenFile.eof())
      { 
      	tokens.clear();
      	single_user.items.clear(); 
      	getline(OpenFile,line);     	
      	if(line.size()!=0) {   
      		if(line.find('|')) {
      			StringSplit(line, tokens,"|");
        	  single_user.id = tokens[0];
        	  single_user.numItems = atoi(tokens[1].c_str()); 
        	  item single_item; 
        	  for (ix=0;ix!=single_user.numItems;ix++) {
        	  	tokens.clear();
        	  	getline(OpenFile,line);     			
          	  StringSplit(line, tokens,"\t");
          	  single_item.id = tokens[0];
          	  single_item.ideal_score = -100; // for the users in the test dataset
          	                                  // ideal score is unkown;
          	  single_item.score = -1; // score needs to be predicted
          	  single_item.confidence = 0.0; // confidence is 0 when initialized         	  
          	  single_user.items.push_back(single_item); 
        	  }
        	  //sort(single_user.items.begin(),single_user.items.end(),increment_item);
        	  users_test.push_back(single_user);  
        	  //cout<<single_user.id<<" and "<<single_user.numItems<<endl;       	  
      		}	   	  
        } 
             	
      } 
	  //cout<<"size = "<<users.size()<<endl;
	  OpenFile.close();
	  OpenFile.clear();		
	  
}

track get_track_from_pool(string trackId)
{
	//cout<<"looking for: "<<trackId<<endl;

	int ix;
	for(ix=0;ix!=tracks.size();ix++)
	{
	//cout<<"tracks[ix].trackId: "<<tracks[ix].trackId<<endl;	
	  if (trackId==tracks[ix].trackId)
	  	return tracks[ix];
	}
	if (ix == tracks.size())
	{
		track single_track;
		single_track.trackId=trackId;
		single_track.albumId="None";
		single_track.artistId="None";		
		return single_track;
	}		 
}

itemType get_item_type(string id)
{
	itemType single_itemType;

	int ix;
	// looking in Artists pool
	for(ix=0;ix!=artists.size();ix++)
	{
	  if (id==artists[ix])
	  {
	  	single_itemType.type = "artist";
	  	single_itemType.iartist = artists[ix];
	  	return single_itemType;
	  }
	}
	// looking in Album pool
	for(ix=0;ix!=albums.size();ix++)
	{
	  if (id==albums[ix].albumId)
	  {
	  	single_itemType.type = "album";
	  	single_itemType.ialbum = albums[ix];
	  	return single_itemType;
	  }
	}	
	// looking in Genre pool
	for(ix=0;ix!=genres.size();ix++)
	{
	  if (id==genres[ix])
	  {
	  	single_itemType.type = "genre";
	  	single_itemType.igenre = genres[ix];
	  	return single_itemType;
	  }
	}	
	// looking in tracks pool
	for(ix=0;ix!=tracks.size();ix++)
	{
	  if (id==tracks[ix].trackId)
	  {
	  	single_itemType.type = "track";
	  	single_itemType.itrack = tracks[ix];
	  	return single_itemType;
	  }
	}
	 
}

/*
float similarity_track(track one, track two)
{
	//cout<<one.trackId<<"|"<<two.trackId<<endl;
	float similarity;
	float sameAlbum, sameArtist, sameGenres;
  vector<string> v(100);
  vector<string>::iterator it;
  int union_size;
  int intersection_size;
  
	
	if (one.trackId==two.trackId)
		return 1.0;
	else
		{
		  it = set_union(one.genres.begin(), one.genres.end(), two.genres.begin(), two.genres.end(), v.begin());
		  union_size = int(it - v.begin());
		  it=set_intersection(one.genres.begin(), one.genres.end(), two.genres.begin(), two.genres.end(), v.begin());
		  intersection_size = int(it - v.begin());
		  // same album  = 5 points
		  sameAlbum = (one.albumId==two.albumId)? 5.0:0.0;	
		  // same artist = 3 points
		  sameArtist = (one.artistId==two.artistId)? 3.0:0.0;
		  // same genre  = 5 point
		  sameGenres = intersection_size*5;
		  
		  similarity = (sameAlbum+sameArtist+sameGenres)/(1*5.0+1*3.0+union_size*5);
	  }
	
	return similarity;
}
*/

float similarity_track_album(itemType one, itemType two)
{
	//cout<<one.trackId<<"|"<<two.trackId<<endl;
	float similarity;
	float sameAlbum, sameArtist, sameGenres;
  vector<string> v(100);
  vector<string>::iterator it;
  int union_size;
  int intersection_size;
  
	if (one.type=="track" && two.type=="track") {
  	if (one.itrack.trackId==two.itrack.trackId)
  		return 1.0;
  	else
  		{
  		  it = set_union(one.itrack.genres.begin(), one.itrack.genres.end(), two.itrack.genres.begin(), two.itrack.genres.end(), v.begin());
  		  union_size = int(it - v.begin());
  		  it=set_intersection(one.itrack.genres.begin(), one.itrack.genres.end(), two.itrack.genres.begin(), two.itrack.genres.end(), v.begin());
  		  intersection_size = int(it - v.begin());
  		  // same album  = 5 points
  		  sameAlbum = (one.itrack.albumId==two.itrack.albumId)? 5.0:0.0;	
  		  // same artist = 3 points
  		  sameArtist = (one.itrack.artistId==two.itrack.artistId)? 3.0:0.0;
  		  // same genre  = 5 point
  		  sameGenres = intersection_size*5;
  		  
  		  similarity = (sameAlbum+sameArtist+sameGenres)/(1*5.0+1*3.0+union_size*5);
  	  }  	
  	return similarity;
  }
  else if (one.type=="album" && two.type=="album") {
  	if (one.ialbum.albumId==two.ialbum.albumId)
  		return 1.0;
  	else
  		{
  		  it = set_union(one.ialbum.genres.begin(), one.ialbum.genres.end(), two.ialbum.genres.begin(), two.ialbum.genres.end(), v.begin());
  		  union_size = int(it - v.begin());
  		  it=set_intersection(one.ialbum.genres.begin(), one.ialbum.genres.end(), two.ialbum.genres.begin(), two.ialbum.genres.end(), v.begin());
  		  intersection_size = int(it - v.begin());
  		  // same artist = 10 points
  		  sameArtist = (one.ialbum.artistId==two.ialbum.artistId)? 10.0:0.0;
  		  // same genre  = 5 point
  		  sameGenres = intersection_size*5;
  		  
  		  similarity = (sameArtist+sameGenres)/(1*10.0+union_size*5);
  	  }  	
  	return similarity;  	
  }
  else
  	return 0.0;
}

/*
 * rough version, based on same item
*/
float similarity_user_r(user one, user two)
{
	float similarity=0;
	int ix,it;

	for(ix=0;ix!=one.numItems;ix++)
	{  
		for(it=0;it!=two.numItems;it++)
		  if (one.items[ix].id==two.items[it].id) 
		  {
				similarity++;
				break;
      } 
	}
	
	return similarity/one.numItems;
}

/*
 * precise version, based on similar item
*/
float similarity_user_p(user one, user two)
{
	float similarity=0, temp, max;
	itemType item_one, item_two;
	int ix,iy;
	int it,is;
	
	for(ix=0;ix!=one.numItems;ix++)
	{ 
		max = 0;
		item_one = get_item_type(one.items[ix].id);
		for(it=0;it!=two.numItems;it++)
		  if (one.items[ix].id==two.items[it].id) break;
  	
		if (it!=two.numItems) // if can find the same track, add 1 to similarity
			{
				//cout<<"find same item"<<endl; 
				similarity++;
			}
		else if (item_one.type!="genre" && item_one.type!="artist")// otherwise, try to find some similar track in user two's items
			{
				//cout<<"track or album: no same item found"<<endl;				
				for(iy=0;iy!=two.numItems;iy++)
				{
					item_two = get_item_type(two.items[iy].id);			
  				temp = similarity_track_album(item_one, item_two);
  				//cout<<"similarity_track = "<<temp<<endl;                        
  				if (temp>max) 
  					{
  						max = temp;
  						//is = iy;					
  					}
				}
  			similarity += max;		
			}
			else
				{
					;//cout<<"genre and artist"<<endl;
				}
	}
	similarity = similarity/one.numItems;
	//two.items[iy].ideal_score
	
	return similarity;
}
/*
float similarity_user(user one, user two)
{
	float similarity=0;
	float confidence=0;
	float temp=0;
	float max=0;
  item max_track;
	int ix,iy;
	int it;
	
	//cout<<one.id<<"|"<<two.id<<endl;
	//cout<<one.numItems<<"|"<<two.numItems<<endl;
  //cout<<one.items.size()<<"|"<<two.items.size()<<endl;
  //cout<<one.items[0].id<<"|"<<two.items[0].id<<endl;
	for(ix=0;ix!=one.numItems;ix++)
	{ 
		temp=0;
		max=0;
		confidence=0;
		cout<<"haha1"<<endl; 
		for(it=0;it!=two.numItems;it++)
		  if (one.items[ix].id==two.items[it].id) break;
		
		cout<<"haha2"<<endl;   	
		if (it!=two.numItems) // if can find the same track, add 1 to similarity
			{
				cout<<"find same"<<endl; 
				similarity++;
				confidence =1.0;
				max_track = two.items[it];
			}
		else // otherwise, try to find some similar track in user two's items
			{
				cout<<"no same found"<<endl;
				cout<<one.items[ix].id<<endl;
				//cout<<get_track_from_pool(one.items[ix].id).trackId<<endl;
				//cout<<get_track_from_pool(one.items[ix].id).albumId<<endl;
				//cout<<get_track_from_pool(one.items[ix].id).artistId<<endl;
				//cout<<"get track okay"<<endl;
				
				for(iy=0;iy!=two.numItems;iy++)
				{
					temp = similarity_track(get_track_from_pool(one.items[ix].id),
					                        get_track_from_pool(two.items[iy].id) );
					cout<<"similarity_track = "<<temp<<endl;                        
					if (temp>max) 
						{
							max_track = two.items[iy];
							max = temp;						
					  }
				}
				cout<<"max = "<<max<<endl;   
				similarity += max;
				confidence = max;					
			}
			if (confidence>one.items[ix].confidence) {
			  one.items[ix].score = max_track.score;
			  one.items[ix].confidence = confidence;
			}
	}
	
	return similarity;
}
*/

bool increment_user  (user i,user j,user c) { return ( similarity_user_p(c,i)<similarity_user_p(c,j) ); }
bool decrement_user  (user i,user j,user c) { return ( similarity_user_p(c,i)>similarity_user_p(c,j) ); }

/*
 * user one is the one needs prediction
 * user two is the one in trainning data set with maximum similarity with user one
*/
user update_score(user one, user two)
{
	float temp, max;
	float confidence=0;
	itemType item_one, item_two;
	int ix,iy;
	int it,is;
	
	for(ix=0;ix!=one.numItems;ix++)
	{ 
		max = 0;
		confidence = 0;
		is =-1;
		item_one = get_item_type(one.items[ix].id);
		for(it=0;it!=two.numItems;it++)
		  if (one.items[ix].id==two.items[it].id) break;
  	
		if (it!=two.numItems) // if can find the same track, add 1 to similarity
			{
				//cout<<"find same item"<<endl; 
				confidence =1.0;
				is = it;
			}
		else if (item_one.type!="genre" && item_one.type!="artist")// otherwise, try to find some similar track in user two's items
			{
				//cout<<"track or album: no same item found"<<endl;				
				for(iy=0;iy!=two.numItems;iy++)
				{
					item_two = get_item_type(two.items[iy].id);			
  				temp = similarity_track_album(item_one, item_two);
  				//cout<<"similarity_track = "<<temp<<endl;                        
  				if (temp>0 && temp>max) 
  					{
  						max = temp;
  						is = iy;					
  					}
				}
				//cout<<"max = "<<max<<endl;
  			confidence = max;		
			}
			else
				{
					//cout<<"genre and artist"<<endl;
					is = -1;
				}
		if (one.items[ix].score<0 && is>=0)
		{		
			//cout<<"5555"<<endl;
		  one.items[ix].score = two.items[is].ideal_score;
		  //cout<<two.items[is].id<<" and "<<two.items[is].score<<endl;
		  //cout<<one.items[ix].id<<" and "<<one.items[ix].score<<endl;
		  one.items[ix].confidence = confidence;
		}
	}
	
	return one;
}
int main(int argc, char *argv[])
{
    int ix,iy;
    int it,is;
    float max_sim, temp_sim;
	  string dir = "../dataset.track1.sample/";
          cout<<dir<<endl;
	  read_input(dir);
	  read_validationUser(dir);
	  
	  read_testUser(dir);
	  //cout<<similarity_track(tracks[0],tracks[51])<<endl;
	  
	  //cout<<"validation starts"<<endl;
	  //cout<<similarity_user_p(users_validation[0],users[0])<<endl;

    

	  ofstream SaveFile("../result/validation_predicted_results.txt");
	  for(ix=0;ix!=users_validation.size();ix++)
	  {
	  	max_sim = 0;
	  	is = 0;
	  	cout<<"Predicting for: "<<users_validation[ix].id<<endl;
      for(iy=0;iy!=users.size();iy++)
      //for(iy=0;iy!=5;iy++)
      {
      	//cout<<"current user for check: "<<users[iy].id<<"|"<<users[iy].numItems<<":"<<endl;
      	 temp_sim = similarity_user_p(users_validation[ix],users[iy]);
      	 if (temp_sim>max_sim)
      	 {	
      	 	 max_sim = temp_sim;
      	 	 is = iy;
      	 }
      	//cout<<similarity_user_p(users_validation[ix],users[iy])<<endl;
      }
      
      users_validation[ix] = update_score(users_validation[ix],users[is]);
      

      
      SaveFile<<users_validation[ix].id<<"|"<<users_validation[ix].numItems<<endl;
      for(it=0;it!=users_validation[ix].numItems;it++)
      {
      	SaveFile<<users_validation[ix].items[it].id<<"\t"<<users_validation[ix].items[it].score;
      	SaveFile<<"\t(ideal_score: "<<users_validation[ix].items[it].ideal_score<<")(";
        SaveFile<<"confidence: "<<users_validation[ix].items[it].confidence<<")"<<endl;
      	cout<<users_validation[ix].items[it].id<<"\t"<<users_validation[ix].items[it].score;
      	cout<<"\t(ideal_score: "<<users_validation[ix].items[it].ideal_score<<")(";
        cout<<"confidence: "<<users_validation[ix].items[it].confidence<<")"<<endl;        
      	
      }     
	  }
 	  
	  
	  
	  
    //system("PAUSE");
    //return EXIT_SUCCESS;
}
