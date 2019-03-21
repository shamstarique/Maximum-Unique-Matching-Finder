#include "suffix_array.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

//TODO: give two text file inputs that contain strings

struct Suffix{
  int index;
};

void sortSuffixArray(vector <Suffix> &suffix_array, vector< char> &sequence){
   int i, j;
   bool swapped; 
   for (i = 0; i < suffix_array.size()-1; i++){ 
     swapped = false; 
     for (j = 0; j < suffix_array.size() -i  -1; j++){ 
        string a = "";
        string b = "";
        
        for(int k = suffix_array.at(j).index; k < sequence.size(); k++){
            a += sequence.at(k);
        }
        
        for(int k = suffix_array.at(j+1).index; k < sequence.size(); k++){
            b += sequence.at(k);
        }
        
        //if (arr[j] > arr[j+1]){ 
        if(a.compare(b) > 0){
           int temp = suffix_array.at(j).index;
           suffix_array.at(j).index = suffix_array.at(j+1).index;
           suffix_array.at(j+1).index = temp;
           
           swapped = true; 
        } 
     } 
  
     // IF no two elements were swapped by inner loop, then break 
     if (swapped == false) 
        break; 
   }
    
    return;
}


//TODO:this implementation is n^2. I can improve to nlogn using doubling technique. Or even to linear using dynamic programming
void createSuffixArray(vector <Suffix> &suffix_array, vector< char> &sequence){
    for(int i = 0; i < sequence.size(); i++){
        Suffix s;
        s.index = i;
        suffix_array.push_back(s);
    }
    sortSuffixArray(suffix_array, sequence);
    return;
}

//check a suffix array for a suffix using binary search. char_sequence is the sequence that is used to generate the suffix_vector
bool searchSuffixArray(string s, vector <Suffix> & suffix_vector, vector <char> & sequence){
    int top = 0;
    int bot = suffix_vector.size()-1;
    int mid;
    
    
 
    int iter = 0;
    while(top <= bot && iter <= 10){
        if(top == bot){
            mid = bot;
        }else{
            mid = top + ((bot - top) / 2);
        }
        cout<<"TOP: "<<top<<" BOT: "<<bot<<" MID: "<<mid<<endl;
        string check_suffix = "";
        
        for(int k = suffix_vector.at(mid).index; k < sequence.size(); k++){
            check_suffix += sequence.at(k);
        }
        cout<<"s = "<<s<<". check_Suffix = "<<check_suffix<<endl;
        if(s.compare(check_suffix) == 0){
            return true;
        }else if(s.compare(check_suffix) < 0){
            bot = mid-1;
        }else{
            
            top = mid+1;
        }
        iter++;
    }
    
    return false;
}

void findMUM(vector<char> &sequence1, vector<char> &sequence2){
    vector< Suffix> suffix_array1;
    vector< Suffix> suffix_array2;
    
    createSuffixArray(suffix_array1, sequence1);
    createSuffixArray(suffix_array2, sequence2);
    
    int largestMUM = -1;
    int largest_mum_size = 0;
    
    for(int i = 0; i < suffix_array2.size(); i++){
        string s = "";
        int temp_mum_size = 0;
        
        for(int k = suffix_array2.at(i).index; k< sequence2.size(); k++){
            s += sequence2.at(k);
            temp_mum_size++;
        }
        
        if(searchSuffixArray(s,suffix_array1, sequence1)){
            if(temp_mum_size > largest_mum_size){
                largest_mum_size = temp_mum_size;
                largestMUM = suffix_array2.at(i).index;
            }
        }
    }
    
    cout<<"largest mum is of size: " <<largest_mum_size<< " and starts at index ";
    cout<<largestMUM<<" in sequence 2"<<endl<<"The MUM is: "<<endl;
    
    string s = "";
        
    for(int k = largestMUM; k< sequence2.size(); k++){
        cout<<sequence2.at(k);
    }
    
    cout<<endl;
    return;
} 

void printAllSuffixes(vector<Suffix> &suffixes, vector<char> &sequence){
    for(int i = 0; i <suffixes.size(); i++){
        string check_suffix = "";
        for(int k = suffixes.at(i).index; k< sequence.size(); k++){
            check_suffix += sequence.at(k);
        }
        cout<<"Suffix at position "<<i<<"with index value "<<suffixes.at(i).index<<" in suffix_vector is "<<check_suffix<<endl;
    }
    
    return;
}

void printSequence(vector < char > &sequence){
    for(unsigned int i = 0; i < sequence.size(); i++){
        cout<< sequence.at(i)<<" ";
    }
    cout<<endl;
}

void printSuffixArray(vector <Suffix> &sequence){
    for(int i = 0; i < sequence.size(); i++){
        cout<< sequence.at(i).index<<" ";
    }
    cout<<endl;
}


int main(){
    
    vector <char> char_sequence;
    vector <char> char_sequence2;
    
    vector< Suffix> suffix_array;
    vector<Suffix> suffix_array2;
    
    //test sequence TODO: read in actual sequence from file later
    char_sequence.push_back('A'); 
    char_sequence.push_back('T'); 
    char_sequence.push_back('A'); 
    char_sequence.push_back('A'); 
    char_sequence.push_back('T'); 
    char_sequence.push_back('A'); 
    char_sequence.push_back('C'); 
    char_sequence.push_back('G'); 
    char_sequence.push_back('A'); 
    char_sequence.push_back('T'); 
    char_sequence.push_back('A'); 
    char_sequence.push_back('A'); 
    char_sequence.push_back('T'); 
    char_sequence.push_back('A'); 
    char_sequence.push_back('A'); 
    char_sequence.push_back('$'); 
    
    char_sequence2.push_back('A'); 
    char_sequence2.push_back('T'); 
    char_sequence2.push_back('A'); 
    char_sequence2.push_back('A'); 
    char_sequence2.push_back('T'); 
    char_sequence2.push_back('A'); 
    char_sequence2.push_back('C'); 
    char_sequence2.push_back('T'); 
    char_sequence2.push_back('A'); 
    char_sequence2.push_back('T'); 
    char_sequence2.push_back('A'); 
    char_sequence2.push_back('A'); 
    char_sequence2.push_back('T'); 
    char_sequence2.push_back('A'); 
    char_sequence2.push_back('A'); 
    char_sequence2.push_back('$'); 
    
    
    //initialize all elements in int_suffix_array to correct sequence for next loop
   
    createSuffixArray(suffix_array, char_sequence);
    printSequence(char_sequence);
    printSuffixArray(suffix_array);
    
    printAllSuffixes(suffix_array, char_sequence);
    
    
    clock_t start = clock();
    findMUM(char_sequence, char_sequence2);
    double duration = ((clock()-start) / (double) CLOCKS_PER_SEC);
    cout<<"Time to finish: "<<duration << " seconds.\n";
    
    
return 0;

}