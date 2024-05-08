#include<iostream>
#include<string>
using namespace std;

bool askQuestion(const string &ques){
    cout<<ques<<" (y/n) : ";
    char res;
    cin>>res;
    return (res=='y' || res=='Y');
}

bool diagnoseFever(){
    bool temp = askQuestion("Do you have body temeperature above 37.5 C?");
    bool chills = askQuestion("Do you experience chills?");
    return (temp || chills);
}

bool diagnoseCold(){
    bool runny = askQuestion("Do you have runny or stuffy nose?");
    bool sneezing = askQuestion("Are you sneezing frequently?");
    return (runny && sneezing);
}

bool diagnoseAllergies(){
    bool itching = askQuestion("Do you experience any itching or smelling ?");
    bool redness = askQuestion("Do you have red and watery eyes?");
    return (itching && redness);
}

bool diagnoseFlue(){
    bool aches = askQuestion("Do you have body aches?");
    bool fatigue = askQuestion("Do you feel tired or fatigued?");
    bool temp = askQuestion("Do you have body temperature above 38 C");
    return (aches && fatigue && temp);
}

bool diagnoseStrepThroat(){
    bool sore = askQuestion("Do you have sore throat?");
    bool swollen = askQuestion("Are your tonsils swollen?");
    return (sore && swollen);
}

bool diagnoseFoodPoisoning(){
    bool nuasea = askQuestion("Do you feel nauseous?");
    bool vomiting = askQuestion("Have you been vomitting?");
    bool diarhea = askQuestion("Do you have diarhea?");
    return (nuasea && vomiting && diarhea);
}

bool diagnoseAppendicitis(){
    bool pain = askQuestion("Do you have abdominal pain ?");
    bool apetite = askQuestion("Do you loss your apetite ?");
    return (pain || apetite);
}

int main(){
    cout<<"\nWelcome to the Expert System for Medical Diagnosis: "<<endl;

    bool hasFever = diagnoseFever();
    bool hasCold = diagnoseCold();
    bool hasAllergies = diagnoseAllergies();
    bool hasFlu = diagnoseFlue();
    bool hasStrepThroat = diagnoseStrepThroat();
    bool hasFoodPoisoning = diagnoseFoodPoisoning();
    bool hasAppendicitis = diagnoseAppendicitis();

    if(hasFever){
        cout<<"\nYou may have fever."<<endl;
    }
    if(hasCold){
        cout<<"\nYou may have cold."<<endl;
    }
    if(hasAllergies){
        cout<<"\nYou may have allergies."<<endl;
    }
    if(hasFlu){
        cout<<"\nYou may have Flu."<<endl;
    }
    if(hasStrepThroat){
        cout<<"\nYou may have throat infection."<<endl;
    }
    if(hasFoodPoisoning){
        cout<<"\nYou may have food poisoning."<<endl;
    }
    if(hasAppendicitis){
        cout<<"\nYou may have appendicitis."<<endl;
    }
    if(!hasFever && !hasCold && !hasAllergies && !hasFlu && !hasStrepThroat && !hasFoodPoisoning && !hasAppendicitis){
        cout<<"\nNo specific diagnosis can be made based on provided symtoms."<<endl;
    }
}