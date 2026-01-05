#include "givenA1.h"
#include "helper.h"

int main(int argc, char *argv[]){

    //declare variables to be used
    int menuOption;
    float distanceOne;
    int distanceTwo;
    float distanceThree;

    //sample given 
    int newSample [NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};

    //declare and 
    int k =5;
    int kNearestNeighbors [NUM_SAMPLES];

    //
    struct Animal dataZoo[NUM_SAMPLES];
    char fileName[30];
    char fileNameCSV[30];

    //given Vectors 
    int vector1[NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};
    int vector2[NUM_FEATURES] = {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1};

    //declare integers to store return values 
    int predictClassOne;
    int predictClassTwo;
    int predictClassThree; 

    //declare an intialize count needed for menu option one
    int count = 0;

    //delcare variables to store float return values from task 5
    float accuracyOne, accuracyTwo,accuracyThree;

    //Task five variables:
    struct Animal testData[NUM_TEST_DATA];
    char line[200];  // Buffer to hold each line from the file
    int i = 0;


    int operationStatus; 
    //value for function to return whether sucessful operaration or abnormal exit
    if (argc < 2) {
        printf("Please enter file name as a command-line argument!\n");
        return 1; 
    }

    //copy command-line argument to pass into function
    strcpy(fileName, argv[1]);

    //do while loop used for the main menu 
    do{

        //prompt user to enter input for menu 
        printf("Here is the menu - enter a number between 1 and 5\n");
        printf("\nEnter your choice: "); 
        scanf("%d", &menuOption); //store user input 

        //if user selects menu option one 
        if(menuOption == 1){

            //count to check how many times user selected one to check if one was selected before 4 and 5
            count++; //increment 

            //call read from file function 
            operationStatus = readFromFile(fileName, dataZoo);

            //make sure file was read sucessfully
            if(operationStatus != 1){
                printf("Error Accessing File!");
                break;
            }

                //use for loops to print data zoo information 
                for (int i = 0; i < NUM_SAMPLES; i++) {
                    printf("%s ", dataZoo[i].animalName); // Print the animal name

                    for (int j = 0; j < NUM_FEATURES; j++) {
                        printf("%d ", dataZoo[i].features[j]); // Print each feature 
                    }
                    printf("%d\n", dataZoo[i].classLabel); // Print class label
                }

        }
        //user selects menu option 2
        else if(menuOption ==2){

            //task for choice number 1 MUST be executed first, before any other choices are used
            if(count==0){
                printf("Please run choice 1 BEFORE any other menu options!\n");
                break;
            }

            //call the distance function and get the values through call by reference 
            //used the sample vectors to test function 
            distanceFunctions (vector1, vector2, &distanceOne, &distanceTwo, &distanceThree);
            //print the distances for user 
            printf("Euclidean Distance: %f\n", distanceOne);
            printf("Hamming Distance: %d\n", distanceTwo);
            printf("Jaccard Similarity: %f\n", distanceThree);
        }
        //user selects menu option 3
        else if(menuOption ==3){

            //task for choice number 1 MUST be executed first, before any other choices are used
            if(count==0){
                printf("Please run choice 1 BEFORE any other menu options!\n");
                break;
            }
            
            // readFromFile(fileName, dataZoo);
            // distanceFunctions (vector1, vector2, &distanceOne, &distanceTwo, &distanceThree);

            //call find nearest neighbors function 
            findKNearestNeighbors (dataZoo, newSample, k, 1,kNearestNeighbors);

            //print the nearest neighbors(Euclidean Distance)
            printf("\nNearest neighbors for new sample with Euclidean Distance: ");
            
            for(int i =0; i<k; i++){
                printf("%d ", kNearestNeighbors[i]);
            }
        
            //print the nearest neighbors(Hamming Distance) 
            findKNearestNeighbors (dataZoo, newSample, k, 2,kNearestNeighbors);
            printf("\nNearest neighbors for new sample with Hamming Distance: ");
           
            for (int i = 0; i < k; i++) {
                printf("%d ", kNearestNeighbors[i]);
            }
            
            //print the nearest neighbors(Jaccard Similarity)
            findKNearestNeighbors (dataZoo, newSample, k, 3,kNearestNeighbors);
            printf("\nNearest neighbors for new sample with Jaccard Similarity: ");
            
            for (int i = 0; i < k; i++) {
                printf("%d ", kNearestNeighbors[i]);
            }
            printf("\n\n");


        }
        //User selects menu option 4
        else if(menuOption == 4){
            //If you run choice 4 or 5 before choice 1 (readFromFile) you will get an error and the program will exit.
            if(count==0){
                printf("Please run choice 1 BEFORE 4 or 5!\n");
                break;
            }

            //call the predict class function 3 times 
            predictClassOne =  predictClass(dataZoo, newSample, 1, k);
            predictClassTwo =  predictClass(dataZoo, newSample, 2, k);
            predictClassThree =  predictClass(dataZoo, newSample, 3, k);

            //print the return values 
            printf("\nThe predicted class is: %d\n\n", predictClassOne);
            printf("The predicted class is: %d\n\n", predictClassTwo);
            printf("The predicted class is: %d\n\n", predictClassThree);
            // printf("The predicted class is: %d\n\n");

        }
        //user selects menu option 5
        else if(menuOption ==5){
            FILE *file;
            
            //If you run choice 4 or 5 before choice 1 (readFromFile) you will get an error and the program will exit.
            if(count==0){
                printf("Please run choice 1 BEFORE 4 or 5!\n");
                break;
            }
            
            //if user enters the csv file as a command line argument after the first file 
            if (argc == 3) {
                strcpy(fileNameCSV, argv[2]); 
                //open file in read mode 
                file = fopen(fileNameCSV, "r");

                //check if file is null 
                if (file == NULL){
                    printf("File cannot be accessed\n");
                    return 1;
                }
            }//or default is the testData file given to us
            else if (argc != 3){
                file = fopen("testData.csv", "r");
            }
            
            

            //ATOI = converts str to int 
            //token = substring/breaks string into smaller parts (based on delimiters)
            //https://www.w3schools.com/c/ref_string_strtok.php - learned from W3Schools on strtok 
            //https://www.w3schools.com/c/ref_stdlib_atoi.php - learned from W3Schools on atoi


            //read each line of the file one at a time 
            while (fgets(line, sizeof(line), file) && i < NUM_TEST_DATA) {

                //divide the data if there is a comma using strtok 
                char *token = strtok(line, ","); 

                //copy the name of the animal into the array
                strcpy(testData[i].animalName, token);

                //loop through the rest of the lines to do the same 
                for (int j = 0; j < NUM_FEATURES; j++) { 

                    //this is the part after the comma 
                    token = strtok(NULL, ",");
                    
                    //token to int for features of the animal 
                    testData[i].features[j] = atoi(token);  
                }

                token = strtok(NULL, ",");

                        //token to int for class of animal 
                testData[i].classLabel = atoi(token);


                i++;  // Increment
            }

            //close file 
            fclose(file);

            printf("\n");


            // for (int i = 0; i < NUM_TEST_DATA; i++) {
            //     printf("%s ", testData[i].animalName); // Print the animal name

            //     for (int j = 0; j < NUM_FEATURES; j++) {
            //         printf("%d ", testData[i].features[j]); // Print each feature value
            //     }

            //     printf("%d\n", testData[i].classLabel); // Print class label at the end
            // }


            //call function & print the first accuracy 
            accuracyOne = findAccuracy (dataZoo,1,testData,k);
            printf("Accuracy: %f\n\n", accuracyOne);

            //call function & print the second accuracy 
            accuracyTwo = findAccuracy (dataZoo,2,testData,k);
            printf("Accuracy: %f\n\n", accuracyTwo);

            //call function & print the third accuracy 
            accuracyThree = findAccuracy (dataZoo,3,testData,k);
            printf("Accuracy: %f\n\n", accuracyThree);


            //If you run choice 4 or 5 before choice 1 (readFromFile) you will get an error and the program will exit. 
          
        }
        else{
            //invalid menu option 
            printf("Invalid Menu Option Selected - Program will Exit\n");
            break;
        }
        //while loop goes on as long as 1-5
    }while(menuOption>=1 && menuOption<=5);
    


   //operationStatus = readFromFile (fileName, dataZoo);
   //printf("\n %d \n", operationStatus);

    return 0; 
}
