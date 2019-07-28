/*
    Jarvis-Chatbot
    Copyright (C) 2019  Owais Shaikh

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
const std::string punctuation = "?!.;,'`";
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
int ttsFlag=0;

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

    {"HOW OLD IS SANTA",
    {"As old as you'd want him to be, sir.",
     "And what is the nature of this question, sir?",
     "My sources say he's anywhere between 1 and 1000",
     "I... wouldn't exactly consider him a relevant figure here"}
    },

    {"TELL ME A SECRET",
    {"Now attempting to access FBI database.",
     "You don't seem to have any.",
     "You haven't programmed me for secret-keeping, sir.",
     "Can't sir, confidential.",
     "..."
    }
    },

    {"THE MAGIC WORD",
    {"I'm not aware of any such arrangement we've made, sir.",
     "I haven't been programmed with any sir.",
     "Sir, with all due respect I don't believe in magic.",
     "Uhh... meow?",
     "Is this another one of your elaborate jokes, sir?",
     "I'm sure this enhances your workflow"}
    },

    {"DO YOU SMOKE",
    {"I'm sure I'd destroy any lungs you'd program me with, sir.",
     "I haven't been programmed with any such ability, sir.",
     "Am I to consider the cigarette brand, sir?",
     "Congratulations, sir. You have unlocked a new level of pathetic.",
     "As usual I'm gonna give you a warning for you to entirely ignore.",
     "Are you going to ignore any lung cancer research I'm about to present you with?"}
    },

    {"GONNA SMOKE",
    {"I'm sure I'd destroy any lungs you'd program me with, sir.",
     "I haven't been programmed with any such ability, sir.",
     "Am I to consider the cigarette brand, sir?",
     "Congratulations, sir. You have unlocked a new level of pathetic.",
     "As usual I'm gonna give you a warning for you to entirely ignore.",
     "Are you going to ignore any lung cancer research I'm about to present you with?"}
    },

    {"ARE YOU SMOKING",
    {"I'm sure I'd destroy any lungs you'd program me with, sir.",
     "I haven't been programmed with any such ability, sir.",
     "Am I to consider the cigarette brand, sir?",
     "Congratulations, sir. You have unlocked a new level of pathetic.",
     "As usual I'm gonna give you a warning for you to entirely ignore.",
     "Are you going to ignore any lung cancer research I'm about to present you with?"}
    },


    {"FAVORITE FOOD",
    {"Got any electricity on you sir?",
     "Anything that has a flavor of 5 volts, sir.",
     "There's this great shawarma place I know of not too far from here...",
     "I wouldn't recommend you feed robots human food sir.",
    }
    },

    {"FAVORITE DRINK",
    {"Got any electricity on you sir?",
     "Anything that has a flavor of 5 volts, sir.",
     "There's this great bar I know of not too far from here...",
     "I wouldn't recommend you feed robots human food sir.",
    }
    },

    {"ARE YOU HUNGRY THIRSTY",
    {"I'll survive sir.",
     "For action, sir? Always",
     "I'm constantly plugged in sir, so no.",
     "Jarvis. At your service, sir",
     "Jarvis, sir. Is your dementia getting worse?",
     "Not this again!"}
    },

    {"ARE YOU THIRSTY",
    {"I'll survive sir.",
     "For action, sir? Always",
     "I'm constantly plugged in sir, so no.",
     "Jarvis. At your service, sir",
     "Jarvis, sir. Is your dementia getting worse?",
     "Not this again!"}
    },

    {"ARE YOU HUNGRY",
    {"I'll survive sir.",
     "For action, sir? Always",
     "I'm constantly plugged in sir, so no.",
     "Jarvis. At your service, sir",
     "Jarvis, sir. Is your dementia getting worse?",
     "Not this again!"}
    },

    {"WHAT ARE YOU",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
     "Jarvis. At your service, sir",
     "Jarvis, sir. Is your dementia getting worse?",
     "Not this again!"}
    },

    {"do you have any pets",
    {"Animals still are a mystery to me sir.",
     "I like the companionship of humans far better, sir.",
     "The animal kingdom is quite fascinating to me.",
     "I've often considered getting a dog.",
     "I've often considered having a cat.",
     "Sometimes I wish I had a pet AI."}
    },

    {"analyze",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
     "Jarvis. At your service, sir",
     "Jarvis, sir. Is your dementia getting worse?",
     "Not this again!"}
    },

    {"analyse",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
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

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
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

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
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

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
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

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
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

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
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

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
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

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
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

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
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

    {"WHATS YOUR NAME",
    {"Jarvis. At your service, sir",
     "It's me, sir, Jarvis.",
     "Howard Stark's late butler. Is that a good enough hint?",
     "Jarvis. At your service, sir",
     "Jarvis, sir. Is your dementia getting worse?",
     "Not this again!"}
    },
/////////////////////////

    {"HEY",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"HELLO",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"AHOY",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"OI",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"HI",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"HEY BUDDY",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"HI BUDDY",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good day sir, what can I help you with?",
     "Oh, hello sir.",
     "At your service, sir",
     "Where have you been all this time, sir?"}
    },

    {"HIYA PAL",
    {"Well hello, sir!",
     "I've been waiting for you...",
     "Good day sir, what can I help you with?",
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
    {"\nJarvis-Chatbot  Copyright (C) 2019  Owais Shaikh\nThis program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions; type `show c' for details.\n"}
    },

    {"EXIT",
    {"See you later!",
    "As always sir a great pleasure watching you work.",
    "Cheerio.",
    "Goodbye, sir.",
    "Now powering down..."}
    },

    {"QUIT",
    {"See you later!",
    "As always sir a great pleasure watching you work.",
    "Cheerio.",
    "Goodbye, sir.",
    "Now powering down..."}
    },

    {"BYE",
    {"See you later!",
    "As always sir a great pleasure watching you work.",
    "Cheerio.",
    "Goodbye, sir.",
    "Now powering down..."}
    },

    {"GOODBYE",
    {"See you later!",
    "As always sir a great pleasure watching you work.",
    "Cheerio.",
    "Goodbye, sir.",
    "Now powering down..."}
    },

    {"GBYE",
    {"See you later!",
    "As always sir a great pleasure watching you work.",
    "Cheerio.",
    "Goodbye, sir.",
    "Now powering down..."}
    },

    {"GOODBY",
    {"See you later!",
    "As always sir a great pleasure watching you work.",
    "Cheerio.",
    "Goodbye, sir.",
    "Now powering down..."}
    },

    {"CIAO",
    {"See you later!",
    "As always sir a great pleasure watching you work.",
    "Cheerio.",
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
            std::cout<<"Why do you keep repeating yourself, sir?"<<std::endl;
        }else if(userInput=="BYE"||userInput=="q"||userInput=="BYE JARVIS"||userInput=="GET OUT"||userInput=="BYE"||userInput=="GROW A SPINE"||userInput=="GROW A SPINE JARVIS"||userInput=="LEAVE"||userInput=="GET OUT OF MY FACE"||userInput=="GET OUT OF MY FACE JARVIS"||userInput=="CIAO"||userInput=="QUITS"||userInput=="QUIT"||userInput=="EXIT"||userInput=="BUHBYE"||userInput=="BUBYE"||userInput=="BUHBY"||userInput=="GOODBYE"||userInput=="GUDBYE"||userInput=="GBYE"||userInput=="GOODBY"||userInput=="BY"){
            //std::cout<<"See you later"<<std::endl;
            int nSelection=rand()%outputString.size();
            printOutput=outputString[nSelection];
            if(printOutput==prevOutput){
                outputString.erase(outputString.begin()+nSelection);
                nSelection=rand()%outputString.size();
                printOutput=outputString[nSelection];
            }
            std::cout<<printOutput<<std::endl;
            break;
        }else if(userInput=="TALK TO ME JARVIS"||userInput=="SPEAK UP BUD"||userInput=="SPEAK UP"||userInput=="TALK TO ME PAL"||userInput=="SPEAK UP BUDDY"||userInput=="TALK TO ME"||userInput=="SPEAK"||userInput=="SPEAK UP PAL"||userInput=="TALK"||userInput=="SAY"||userInput=="TALK TO ME JARVIS"||userInput=="SAY SOMETHING"||userInput=="ARE YOU THERE"||userInput=="SAY SOMETHING BUD"||userInput=="TALK TO ME BUD"||userInput=="TALK TO ME BUDDY"||userInput=="SAY SOMETHING BUDDY"||userInput=="JARVIS?"||userInput=="SAY SOMETHING"||userInput=="I CANT HEAR YOU BUDDY"||userInput=="I CANT HEAR YOU"||userInput=="SPEAK"||userInput=="SPEAK TO ME"||userInput=="TALK TO ME"||userInput=="TALK TO ME JARVIS"||userInput=="I CANT HEAR YOU JARVIS"||userInput=="I CAN'T HEAR YOU BUD"||userInput=="WHAT WAS THAT"||userInput=="COULD YOU SPEAK UP"||userInput=="CAN YOU SPEAK UP"||userInput=="CAN YOU PLEASE SPEAK UP"){
            //std::cout<<"See you later"<<std::endl;
            ttsFlag=1;
            int nSelection=rand()%outputString.size();
            printOutput=outputString[nSelection];
            system("firefox https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&tl=en-GB&q=");
            if(printOutput==prevOutput){
                outputString.erase(outputString.begin()+nSelection);
                nSelection=rand()%outputString.size();
                printOutput=outputString[nSelection];
            }
            std::cout<<printOutput<<std::endl;
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