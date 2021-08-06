#include<bits/stdc++.h>
using namespace std;

int main(){
    fstream fout; // for taking input in a separate file
    fout.open("inputfile", ios::out | ios::trunc);
    srand(time(0));
    int i=0;
    int n = 10000; // number of processes
    int len = 5; 
    int inst; // generating random numbers
    string s;
    fout<<'1'<<'0'<<'0'<<'0'<<'0'<<"\n";

    // Burst Time of all the processes
    i=0;
    while(i < 100 && i < n){
        inst = (rand() % 50) + 1; // burst time will be between 0 to 50 for 1st 100 processes
        string s; // storing random no in a string
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = '0' + s;
            }
            else{
                s = (char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;    
    }
    while(i < n){
        inst = (rand() % 300) + 1; // burst time will be between 0 to 300 for the remaining processes
        string s;
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = '0' + s;
            }
            else{
                s = (char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;
    }

    // Arrival time of all the processes
    i=0;
    while(i < n && i < 100){
        inst = rand() % 100 + 1; // 0 <= arrival time <=100 for 1st 100 processes
        string s;
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = '0' + s;
            }
            else{
                s = (char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;  
    }
    while(i < n && i < n/10){
        inst = rand() % 950 + 50; // 50 <= arrival time <= 1000
        string s;
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = '0' + s;
            }
            else{
                s = (char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;  
    }
    while(i < n && i < 3*n/100){
        inst = rand() % 2000 + 1000; // 1000 <= arrival time <= 3000
        string s;
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = '0' + s;
            }
            else{
                s = (char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;  
    }
    while(i < n && i < 7*n/100){
        inst = rand() % 3000 + 3000; // 3000 <= arrival time <= 6000
        string s;
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = '0' + s;
            }
            else{
                s = (char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;  
    }
     while(i < n && i < 9*n/100){
        inst = rand() % 2000 + 6000; // 6000 <= arrival time <= 8000
        string s;
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = '0' + s;
            }
            else{
                s = (char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;  
    }
    while(i < n){
        inst = rand() % 2000 + 8000; // 8000 <= arrival time <= 10,000
        string s;
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = '0' + s;
            }
            else{
                s = (char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;  
    }

    // priorities of all the processes
    i=0;
    while(i < n && i < 100){
        inst = rand() % 5 + 1; // 1 <= priorities <=5 for 1st 100 processes
        string s;
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = "0" + s;
            }
            else{
                s = (char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;
    }
    while(i < n){ 
        inst = rand() % 50 + 1; // 1 <= priorities <= 50
        string s;
        for(int i=0; i<len; i++){
            if(inst == 0){
                s = "0" + s;
            }
            else{
                s =(char)((inst % 10) + '0') + s;
            }
            inst = inst/10;
        }
        for(int i=0; i<len; i++){
            fout<<s[i];
        }
        fout<<"\n";
        i++;
    }
}




