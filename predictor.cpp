#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// function for predict marks
double predictMarks(double attendance, double studyHours, 
                    double internalMarks, double assignments,
                    double w1, double w2, double w3, 
                    double w4, double b) {

    return w1 * attendance + w2 * studyHours + 
           w3 * internalMarks + w4 * assignments + b;
}


int main() {
    cout <<"SIMPLE MARKS PREDICTOR"<<endl;
    
    // Data for Training 
    vector<double>studyHours = {5, 7, 4, 8, 3};
    vector<double>internalMarks = {78, 85, 70, 92, 65};
    vector<double>attendance = {85, 92, 78, 95, 70};
    vector<double>assignments = {90, 95, 80, 98, 75};
    vector<double>finalMarks = {82, 88, 75, 94, 68};
    
    int n = assignments.size();
    
    // Initialize weights
    double w1=0.1, w2=0.1, w3=0.1, w4=0.1, b=0;
    double learningRate=0.00001;   
    
    cout << "Training on =" << n << " students\n" << endl;
    
    
    for(int epoch = 0; epoch < 1000; epoch++) {
        double totalLoss = 0;
        
        for(int i = 0; i < n; i++) {
            // Prediction
            double pred = predictMarks(attendance[i], studyHours[i],
                                       internalMarks[i], assignments[i],
                                       w1, w2, w3, w4, b);
            
            // Error calculating
            double error = pred - finalMarks[i];
            totalLoss += error * error;
            
            // Weight updation
            w1 =w1- learningRate*error*attendance[i];
            w2 = w2-learningRate*error*studyHours[i];
            w3 = w3-learningRate*error*internalMarks[i];
            w4 = w4-learningRate*error*assignments[i];
            b  = b-learningRate*error;
        }
        
        if(epoch % 200 == 0) {
            cout << "Epoch:-" << epoch 
                 << " | Average Loss:-" << totalLoss / n << endl;
        }
    }
    
    cout << "\nTraining complete!\n" << endl;
    
    // Testing on training data
    cout << "Testing on training data:" << endl;
    cout << "----" << endl;
    
    for(int i = 0; i < n; i++) {
        double predi = predictMarks(attendance[i], studyHours[i],
                                   internalMarks[i], assignments[i],
                                   w1, w2, w3, w4, b);

        cout << "Actual:-" << finalMarks[i]<<" "
             << "Predicted:-" <<predi<<" "
             << "Difference:-" << abs(finalMarks[i] - predi) 
             << endl;
    }
    
    // Make predictions
    cout <<endl<< "--:MAKE PREDICTIONS:--" << endl;
    
    while(1) {
        double att,study,internal,assign;
        
        cout<<"\nEnter student details:" << endl;
        
        cout<<"Attendance (0-100): ";
        cin >> att;
        
        cout<<"Study Hours(0-10): ";
        cin>>study;
        
        cout<<"Internal Marks(0-100): ";
        cin>>internal;
        
        cout<<"Assignments(0-100): ";
        cin>>assign;
        
        if(att==0 && study==0 && internal==0 && assign==0) {
            break;
        }
        
        double pred = predictMarks(att, study, internal, assign,
                                   w1, w2, w3, w4, b);
        
        cout <<"Predicted Final Marks: "<<pred<<endl;
    }
    
    return 0;
}