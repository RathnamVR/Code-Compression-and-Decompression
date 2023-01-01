/* On my honor, I have
neither given nor received unauthorized aid on this assignment */
/* Index-180523F
Name - Vidushika*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
int binaryToDecimal(int n){
    int num = n;
    int dec_value = 0;
    int base = 1;
 
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
 
    return dec_value;
}

string decToBinary(int n,int l) {
   string output="";
    for (int i = l; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            output=output+"1";
        else
            output=output+"0";
    }
    return(output);
}

string switchbits(string c,int p){
    if (c[p]=='1'){
        c[p]='0';
    }
    else{
        c[p]='1';
    }
    return c;
}

string bitmask (string x, map<string,string> d){
   vector<string> bitmask={"1111","1110","1101","1100","1011","1010","1001","1000","0111","0110","0101","0100","0011","0010","0001","0000"};
   string code="001";
   for (string b:bitmask){
      for (int i=0;i<x.length();i++){
         string substring = x.substr(i, 4);
         int d1=binaryToDecimal(stoi(b));
         int d2=binaryToDecimal(stoi(substring));
         int xorresult=(d2)^(d1);
         string xorresultstring = decToBinary(xorresult,3);
         string replacestring=to_string(xorresult);
         string copyofx=x;
         copyofx.replace(i,4,xorresultstring);
         for (auto h:d){
            if (copyofx==h.second){
               string position=decToBinary(i,4);
               string compress=code+position+b+h.first;
               return(compress);
            }
         }
      }
   }
   return("0");


}
string bitmismatch (string x, map<string,string> d){
   vector<int> mismatch;
   vector<vector<int>> mismatch_index;
   for (auto h:d){
     int c=0;
     vector<int> index;
     for (int i=0;i<x.size();i++){
      if (x[i]!=h.second[i]){
            c++; 
            index.push_back(i); 
            
      }
   }
   mismatch_index.push_back(index);
   mismatch.push_back(c);
   }
   int q=0;
   for (auto h:d){
      string entry=h.first;
      if (mismatch[q]==1){
         string code="010";
         vector<int> temp=mismatch_index[q];
         string position=decToBinary(temp[0],4);
         string compress=code+position+entry;
         return(compress);
      }
      else if (mismatch[q]==2){
         vector<int> temp=mismatch_index[q];
         int a1=temp[0];
         int a2=temp[1];
         if (a2-a1==1){
               string code="011";
               string position=decToBinary(a1,4);
               string compress=code+position+entry;
               return(compress);
         }
         else{
               string code="100";
               string position1=decToBinary(a1,4);
               string position2=decToBinary(a2,4);
               string compress=code+position1+position2+entry;
               return(compress);
         }
      }
      q++;
   }
   string noncompress="0";
   return(noncompress);
}
string directmatching (string x, map<string,string> d){
   string code="101";
   int c=0;
   for (auto h:d){
      if (h.second==x){
         c=1;
         string entry = h.first;
         string compress=code+entry;
         return(compress);
      }
   }
   
      string noncompress="0";
      return(noncompress);
   
}
string originalbit(string x){
   string code="110";
   string compress=code+x;
   return(compress);
}
string finalcompress(string bit, map<string,string> dictionary){
            vector<string> compressways;
            vector<pair<int,int>> compressways_length;
            string y=bitmask(bit,dictionary);
            compressways.push_back(y);
            compressways_length.push_back(make_pair(y.length(),0));
            
            string y1=bitmismatch(bit,dictionary);
            compressways.push_back(y1);
            compressways_length.push_back(make_pair(y1.length(),1));

            string y2=directmatching (bit,dictionary);
            compressways.push_back(y2);
            compressways_length.push_back(make_pair(y2.length(),2));
            
            string y3=originalbit(bit);
            compressways.push_back(y3);
            compressways_length.push_back(make_pair(y3.length(),3));
            
            sort(compressways_length.begin(), compressways_length.end());
            for (auto x:compressways_length){
               if (x.first>1){
                  return(compressways[x.second]);
               }
            }
            return("0");

}
int main(int argc,char* argv[]){
 int comordecom=atoi(argv[1]);
 if(comordecom==1){ 
   fstream infile;
   vector<string> original;
   infile.open("original.txt",ios::in); 
   if (infile.is_open()){ 
      string line;
      while(getline(infile, line)){ 
        original.push_back(line);
        
      }}
      infile.close(); 
      vector<pair<int,int>> frequency;
      vector<string> done;
      int i=0;
      for (string x : original){
            int c=0;
            for (string k : done){
               if (x == k){
                  c=1;
                  break;
               }
            }
            if (c!=1){
            int freq = std::count(original.begin(), original.end(), x);
            done.push_back(x);
            frequency.push_back(make_pair(freq, i));
            i++;
            }
      }
      
      sort(frequency.begin(), frequency.end());
      for (int i=0;i<frequency.size();i++){
         for (int t=i;t<frequency.size();t++){
            if ((frequency[i].first==frequency[t].first) && (frequency[i].second<frequency[t].second)){
               pair<int,int> k = frequency[i];
               frequency[i] = frequency[t];
               frequency[t] = k;
            }
         }
      }
      vector<string> sorted_element;
      vector<string> dic_entry={"000","001","010","011","100","101","110","111"};
      map<string,string> dictionary;
      vector<int> sorted_freq;
      int c=0;
      for (int i=frequency.size()-1;i>frequency.size()-9;i--){
         sorted_freq.push_back(frequency[i].first);
         dictionary[dic_entry[c]]=(done[frequency[i].second]);
         c++;
      }

      int r=0;
      vector<vector<string>> repeats;
      while (r<original.size()){
         vector<string> repeat;
         repeat.push_back(original[r]);
         int u=1;
         for (int j=1;j<=4;j++){
            if (original[r]==original[r+j]){
               repeat.push_back(original[r+j]);
               u++;
            }
            else{
               break;
            }
         }
         r=r+u;
         repeats.push_back(repeat);
      }
      
      vector<string> compress;
      string filecompress="";
      for (auto x:repeats){
         vector<string> temp=x;
         if (x.size()==1){
              string bit=x[0];
              string finalresult=finalcompress(bit,dictionary);
              compress.push_back(finalresult);
              filecompress=filecompress+finalresult;

         }
         else{
            string bit_first=x[0];
            string finalresult=finalcompress(bit_first,dictionary);
            compress.push_back(finalresult);
            filecompress=filecompress+finalresult;
            vector<string> comparisson;
            string code="000";
            string rlefinal="";
            string rle="";
            if (x.size()==2){
                  rle="00";
                  
            }
            else if (x.size()==3){
                  rle="01";
                  
            }
            else if (x.size()==4){
                  rle="10";
                  
            }
            else if (x.size()==5){
                  rle="11";
                  
            }
            rlefinal=code+rle;
            int lengthother=0;
            for (int i=1;i<x.size();i++){
               string finalresult=finalcompress(x[i],dictionary);
               lengthother=lengthother+finalresult.length();
               comparisson.push_back(finalresult);
            }
            if (lengthother<5){
               for (auto x:comparisson){
                  compress.push_back(x);
                  filecompress=filecompress+x;
               }

            }
            else{
               compress.push_back(rlefinal);
               filecompress=filecompress+rlefinal;
            }

         }
      }
      ofstream outfile("cout.txt");
      
      for (int i=0;i<filecompress.length();i=i+32){
         string line=filecompress.substr(i,32);
         if (line.length()==32){
            outfile<<line<<endl;
            
         }
         else{
            int remaining=32-line.length();
            line=line+string(remaining, '1');
            outfile<<line<<endl;
            
         }
      }
      outfile<<"xxxx"<<endl;
      for (auto x:dictionary){
         outfile<<x.second<<endl;
      }
   
   }
   else if(comordecom==2){
      fstream infile;
      string withdictionary="";
      infile.open("compressed.txt",ios::in); 
      if (infile.is_open()){ 
         string line;
         while(getline(infile, line)){ 
            withdictionary=withdictionary+line;
      }}
      infile.close(); 
      string thread="";
      for (char y:withdictionary){
        if (y=='x'){
            break;
        }
        else{
            thread=thread+y;
        }
      }
      map<string,string> dictionary;
      int p=0;
      vector<string> threebit={"000","001","010","011","100","101","110","111"};
      for (char y:withdictionary){
        if (y=='x'){
            int k=p+4;
            for (int i=0;i<8;i++){
               dictionary[threebit[i]]=withdictionary.substr(k,32);
               k=k+32;
            }
            break;
        }
        p++;
      }
      int k=0;
      vector<string> uncompressed;
      for (int i=0; i<thread.length();i=i+k) {
      string start=thread.substr(i,3);
        if (start=="000"){
            int repeat=binaryToDecimal(stoi(thread.substr(i+3,2)));
            for (int r=0;r<repeat+1;r++){
                uncompressed.push_back(uncompressed.back());
            }
            k=5;

        }
        else if (start=="001"){
            string dattach=thread.substr(i+3,12);
            int loc=binaryToDecimal(stoi(dattach.substr(0,5)));
            int bitmask=binaryToDecimal(stoi(dattach.substr(5,4)));
            string coded=dattach.substr(9,12);
             for (auto x:dictionary){
                if (x.first==coded){
                     string entry=x.second;
                     int maskaffected=binaryToDecimal(stoi(entry.substr(loc,4)));
                     int reversexor=maskaffected ^ bitmask;
                     string unmask=decToBinary(reversexor,3);
                     string original=entry.substr(0,loc)+unmask+entry.substr(loc+4,entry.length());
                     uncompressed.push_back(original);
                     
                }
            }
            k=15;
            
        }
        else if (start=="010"){
            string dattach=thread.substr(i+3,8);
            int startloc=binaryToDecimal(stoi(dattach.substr(0,5)));
            string coded=dattach.substr(5,3);
            for (auto x:dictionary){
                if (x.first==coded){
                     string entry=x.second;
                     string original=switchbits(entry,startloc);
                     uncompressed.push_back(original);
                }
            }
            k=11;
        }
        else if (start=="011"){
            string dattach=thread.substr(i+3,8);
            int startloc=binaryToDecimal(stoi(dattach.substr(0,5)));
            int secondloc=startloc+1;
            vector<int> location={startloc,secondloc};
            string coded=dattach.substr(5,3);
            for (auto x:dictionary){
                if (x.first==coded){
                     
                     string entry=x.second;
                     for (int i=0;i<2;i++){
                        entry=switchbits(entry,location[i]);
                     }
                     uncompressed.push_back(entry);
                }
            }
            k=11;
        
        }
        else if (start=="100"){
            string dattach=thread.substr(i+3,13);
            int startloc=binaryToDecimal(stoi(dattach.substr(0,5)));
            int secondloc=binaryToDecimal(stoi(dattach.substr(5,5)));
            vector<int> location={startloc,secondloc};
            string coded=dattach.substr(10,3);
            for (auto x:dictionary){
                if (x.first==coded){
                     string entry=x.second;
                     for (int i=0;i<2;i++){
                        entry=switchbits(entry,location[i]);
                     }
                     uncompressed.push_back(entry);
                }
            }
            k=16;
            
           
        }
        else if (start=="101"){
            string coded=thread.substr(i+3,3);
            for (auto x:dictionary){
                if (x.first==coded){
                       uncompressed.push_back(x.second);
                }
            }
            k=6;
        }
        else if (start=="110"){
            string original=thread.substr(i+3,32);
            k=35;
            
            uncompressed.push_back(original);
        }
      }
      
      ofstream outfile("dout.txt");
      for (string x:uncompressed){
         outfile<<x<<endl;
      }

   }
}