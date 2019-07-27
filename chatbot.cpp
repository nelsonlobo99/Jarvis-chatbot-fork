/*
    Jarvis-Chatbot
    compareStringright (C) 2019  Owais Shaikh

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a compareString of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

char *name="owais";
const int MAX=32;
const std::string punctuation = "?!.;,'";
typedef std::vector<std::string> queryString;
queryString find_match(std::string inputString);
void caseCheck(std::string &str);
void cleanString(std::string &str);
bool isPunc(char c);
void compareString(char *array[], queryString &v);
void inputBuffer(std::string &str);
typedef struct{
    char *inputString;
    char *outputString[MAX];
}record;

record digest[]={
    {"WHAT IS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Take a wild guess.",
     "Jarvis. At your service, sir",
     "Jarvis, sir. Is your dementia getting worse?",
     "Not this again!"}
    },

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
     "Jarvis. At your service, sir",
     "Jarvis, sir. Is your dementia getting worse?",
     "Not this again!"}
    },

    {"HEY",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good Day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"HI",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good Day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"HEY BUDDY",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good Day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"HI BUDDY",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good Day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"HIYA PAL",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good Day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },
    
    {"HOW ARE YOU",
    {"I'm doing alright",
    "I'm fine",
    "Running a little low on memory"}
    },

    {"HELP",
    {"\nHello, I'm Jarvis, a chatbot. You can have a simple conversation \nwith me, by simply typing it below. Nothing \ncomplicated please, I'm still learning, after all!\n"}
    },

    {"ABOUT",
    {"\nJarvis-Chatbot  compareStringright (C) 2019  Owais Shaikh\nThis program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions; type `show c' for details.\n"}
    },

    {"EXIT",
    {"See you later",
    "As always sir a great pleasure watching you work.",
    "Cheerio",
    "Goodbye, sir.",
    "Now powering down..."}
    },

};
size_t loopVar = sizeof(digest)/sizeof(digest[0]);

int main(){
    srand((unsigned) time(NULL));
    system("clear");
    std::string userInput="";
    std::string printOutput="";
    std::string prevOutput="";
    std::string prevInput="";
    while(1){
        std::cout<<" ▶ ";
        prevOutput=printOutput;
        prevInput=userInput;
        std::getline(std::cin, userInput);
        inputBuffer(userInput);
        queryString outputString=find_match(userInput);
        if (userInput==prevInput&&userInput.length()>10){
            std::cout<<"Why do you keep repeating yourself?"<<std::endl;
        }else if(userInput=="BYE"||userInput=="QUIT"||userInput=="EXIT"||userInput=="GOODBYE"||userInput=="GBYE"||userInput=="GOODBY"||userInput=="BY"){
            std::cout<<"See you later"<<std::endl;
            break;
        }else if(outputString.size()==0){
            //unknownInputHandler(userInput);
            std::ofstream toFile;
            toFile.open("unknownInputs.txt", std::ios_base::app);
            toFile<<userInput; 
            toFile<<std::endl;
            std::cout<<"I didn't quite get that."<<std::endl;
        }else{
            int nSelection=rand()%outputString.size();
            printOutput=outputString[nSelection];
            if(printOutput==prevOutput){
                outputString.erase(outputString.begin()+nSelection);
                nSelection=rand()%outputString.size();
                printOutput=outputString[nSelection];
            }
            std::cout<<printOutput<<std::endl;
        }
    }
    return 0;
}

void inputBuffer(std::string &str){
    cleanString(str);
    caseCheck(str);
}

queryString find_match(std::string inputString){
    queryString result;
    for(int i=0; i<loopVar; ++i){
        std::string keyWord(digest[i].inputString);
        if(inputString.find(keyWord) != std::string::npos){
            compareString(digest[i].outputString, result);
            return result;
        }
    }
    return result;
}

void compareString(char *array[], queryString &v){
    for(int i=0; i<MAX; ++i){
        if(array[i]!=NULL){
            v.push_back(array[i]);
        }else{
            break;
        }
    }
}

void caseCheck(std::string &str){
    int len=str.length();
    for( int i=0; i<len; i++){
        if (str[i]>='a' && str[i]<='z'){
            str[i] -= 'a'-'A';
        }
    }
}

bool isPunc(char c){
    return punctuation.find(c) != std::string::npos;
}

void cleanString(std::string &str){
    int len=str.length();
    std::string temp="";
    char prevChar=0;
    for(int i=0; i<len; ++i){
        if(str[i]==' ' && prevChar==' '){
            continue;
        }else if(!isPunc(str[i])){
            temp+=str[i];
        }
        prevChar=str[i];
    }
    str=temp;
}

void unknownInputHandler(std::string &str){  
  std::ofstream toFile;
  toFile.open("unknownInputs.txt", std::ios_base::app);
  toFile<<str; 
}