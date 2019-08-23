//
//  main.cpp
//  generateTasks
//
//  Created by Michael An on 8/21/19.
//  Copyright © 2019 Michael An. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>    // std::random_shuffle
using namespace std;

string mSteer(int rectWidth, int rectHeight, int gapLength, int gapHeight, string nextStage);
string mClick(int rectWidth, int rectHeight, int gapLength, string nextStage);
string mDrag(int rectWidth, int rectHeight, int gapLength, string nextStage);
int* generateRandomOrderArray(int num);

int main(int argc, const char * argv[]) {
    // insert code here...
    string test = "test";
    test += "\n";
    cout << "Hello, World!\n";
    //printf(&test[0]);
    //cout << mDrag(100, 200, 20, "mousedraw.html");
    //be sure that the nums array has same number of elements as the nested loop below produces
    int* nums = generateRandomOrderArray(60);
    int currentnum = 0;
    
    for (int l = 64; l <= 1024; l*= 2){
        for (int w = 8; w <= 64; w*= 2){
            char* curr = (char*) malloc(100);
            char* next = (char*) malloc(100);
            sprintf(curr, "%d.html", nums[currentnum]);
            sprintf(next, "%d.html", nums[currentnum] + 1);
            FILE* steer = fopen(curr, "w");
            fprintf(steer, "%s", &mSteer(l, 200, l, 2*w, next)[0]);
            currentnum++;
            sprintf(curr, "%d.html", nums[currentnum]);
            sprintf(next, "%d.html", nums[currentnum] + 1);
            FILE* click = fopen(curr, "w");
            fprintf(click, "%s", &mClick(w, 200, l, next)[0]);
            currentnum++;
            sprintf(curr, "%d.html", nums[currentnum]);
            sprintf(next, "%d.html", nums[currentnum] + 1);
            FILE* drag = fopen(curr, "w");
            fprintf(drag, "%s", &mDrag(w, 200, l, next)[0]);
            currentnum++;
            free(curr);
            free(next);
        }
    }
    /*
    for (int i = 0; i < 4; i++, w*=2){
        char* curr = (char*) malloc(100);
        char* next = (char*) malloc(100);
        sprintf(curr, "%d.html", nums[i]);
        sprintf(next, "%d.html", nums[i+1]);
        FILE* outputFile = fopen(curr, "w");
        fprintf(outputFile, "%s", &mSteer(800, 100, 800, w, next)[0]);
    }
    */
    /*
    FILE* outputFile = fopen("outputFile", "w");
    if (outputFile == NULL) {
        printf("error: touchOutputFile.txt initialization failed");
        exit(1);
    }
    else {
        fprintf(outputFile, "%s", &mSteer(50, 60, 20, 30, "mousedraw.html")[0]);
    }
     */
    return 0;
}

string mSteer(int rectWidth, int rectHeight, int gapLength, int gapHeight, string nextStage){
    string output = "";
    char* buffer = (char*) malloc(1024);
    //output+= "<!DOCTYPE HTML>\n"; it turns out that rendering with HTML5 breaks the block hitboxes; they'll extend past the image size. On the other hand, rendering in quirks mode works as intended. This bug is the stupidest thing ever.
    output+= "<html>\n";
    output+= "<script type=\"text/javascript\" src=\"draw.js\"></script>\n";
    output+= "<style>\n";
    output+= "div.rectangle {";
    sprintf(buffer, "width: %dpx; height: %dpx; border: 1px solid black;}\n", rectWidth, rectHeight);
    output+= buffer;
    output+= "img.rectangle {";
    sprintf(buffer, "width: %dpx; height: %dpx;}\n", rectWidth, rectHeight);
    output+= buffer;
    output+= "body{margin:0;}\n";
    output+= "#div1 {\n";
    output+= "position:absolute;\n";
    sprintf(buffer, "top:calc(50%% - 0.5 * (%dpx + %dpx));\n", rectHeight, gapHeight);
    //apparently % is escaped with %%, not \%
    output+= buffer;
    output+="left:50%;\n";
    output+="transform:translate(-50%,-50%);}\n";
    output+= "#div2 {\n";
    output+= "position:absolute;\n";
    sprintf(buffer, "top:calc(50%% + 0.5 * (%dpx + %dpx));\n", rectHeight, gapHeight);
    output+= buffer;
    output+= "left:50%;\n";
    output+= "transform:translate(-50%,-50%);}\n";
    output+= "h2, p { padding-left:10px; }\n";
    output+= "h2 { padding-top:20px; }\n";
    output+= "</style>\n";
    output+= "<body onload=\"init()\">\n";
    output+= "<canvas id=\"can\" style=\"position:absolute;\">\n";
    output+= "</canvas>\n";
    output+= "<h2> Steering </h2>\n";
    output+= "<p> Draw a line from left to right between the blocks without touching them. </p>\n";
    output+= "<div id=\"div1\">\n";
    output+= "<img id=\"click1\" src=\"images/purple.png\" class=\"rectangle\">\n";
    output+= "</div>\n";
    output+= "<div id=\"div2\">\n";
    output+= "<img id=\"click2\" src=\"images/purple.png\" class=\"rectangle\">\n";
    output+= "<script>\n";
    output+= "function nextStage() {\n";
    sprintf(buffer, "if (currX > 0.5*(canvas.width + %d)) { console.log(Math.floor(new Date().getTime()/1000.0) + \".\" + new Date().getTime()%%1000 + \",steer,\" + %d + \"px,\" + %d + \"px\"); open(\"%s\", \"_self\") }}", rectWidth, gapLength, rectWidth, &nextStage[0]);
    output+= buffer;
    output+= "</script>\n";
    output+= "</div>\n</body>\n</html>\n";
    free(buffer);

    return output;
}

string mClick(int rectWidth, int rectHeight, int gapLength, string nextStage){
    string output = "";
    char* buffer = (char*) malloc(1024);
    output+= "<!DOCTYPE HTML>\n";
    output+= "<html>\n";
    output+= "<head>\n";
    output+= "<style>\n";
    output+= "div.rectangle {";
    sprintf(buffer, "width: %dpx; height: %dpx; border: 1px solid black;}\n", rectWidth, rectHeight);
    output+= buffer;
    output+= "img.rectangle {";
    sprintf(buffer, "width: %dpx; height: %dpx;}\n", rectWidth, rectHeight);
    output+= buffer;
    output+= "div:hover{ cursor: pointer; }\n";
    output+= "#div1 {\n";
    output+= "position:absolute;\n";
    sprintf(buffer, "left:calc(50%% - 0.5 * (%dpx + %dpx));\n", rectWidth, gapLength);
    output+= buffer;
    output+= "top:50%;\n";
    output+="transform:translate(-50%,-50%); }\n";
    output+= "#div2 {\n";
    output+= "position:absolute;\n";
    sprintf(buffer, "left:calc(50%% + 0.5 * (%dpx + %dpx));\n", rectWidth, gapLength);
    output+= buffer;
    output+= "top:50%;\n";
    output+= "transform:translate(-50%,-50%); }\n";
    output+= "</style>\n";
    output+= "</head>\n";
    output+= "<body>\n";
    output+= "<h2> Point and Click </h2>\n";
    output+= "<p>Click on the left block and then the right block.</p>\n";
    output+= "<div id=\"div1\" class=\"rectangle\">\n";
    output+= "<img id=\"click1\" src=\"images/blue.png\" class=\"rectangle\">\n";
    output+= "</div>\n";
    output+= "<div id=\"div2\" class=\"rectangle\">\n";
    output+= "<img id=\"click2\" src=\"images/yellow.png\" class=\"rectangle\">\n";
    output+= "</div>\n";
    output+= "</body>\n";
    output+= "<script type=\"text/javascript\" src=\"click.js\"> </script>\n";
    output+= "<script>\n";
    sprintf(buffer, "document.getElementById('div2').onclick = function nextStage() { if (document.getElementById('click1').src == document.getElementById('click2').src){ console.log(Math.floor(new Date().getTime()/1000.0) + \".\" + new Date().getTime()%%1000 + \",click,\" + %d + \"px,\" + %d + \"px\"); open(\"%s\", \"_self\"); } }\n", gapLength, rectWidth, &nextStage[0]);
    output+= buffer;
    output+= "</script>\n";
    output+= "</html>\n";
    free(buffer);

    return output;
}


string mDrag(int rectWidth, int rectHeight, int gapLength, string nextStage) {
    string output = "";
    char* buffer = (char*) malloc(1024);
    output+= "<!DOCTYPE HTML>\n";
    output+= "<html>\n";
    output+= "<head>\n";
    output+= "<style>\n";
    output+= "div.rectangle {";
    sprintf(buffer, "width: %dpx; height: %dpx; border: 1px solid black;}\n", rectWidth, rectHeight);
    output+= buffer;
    output+= "img.rectangle {";
    sprintf(buffer, "width: %dpx; height: %dpx;}\n", rectWidth, rectHeight);
    output+= buffer;
    output+= "#div1:hover { cursor:grab; }\n";
    output+= "#div1 {\n";
    output+= "position:absolute;\n";
    sprintf(buffer, "left:calc(50%% - 0.5 * (%dpx + %dpx));\n", rectWidth, gapLength);
    output+= buffer;
    output+= "top:50%;\n";
    output+="transform:translate(-50%,-50%); }\n";
    output+= "#div2 {\n";
    output+= "position:absolute;\n";
    sprintf(buffer, "left:calc(50%% + 0.5 * (%dpx + %dpx));\n", rectWidth, gapLength);
    output+= buffer;
    output+= "top:50%;\n";
    output+= "transform:translate(-50%,-50%); }\n";
    output+= "</style>\n";
    output+= "</head>\n";
    output+= "<body>\n";
    output+= "<h2>Drag and Drop</h2>\n";
    output+= "<p>Drag the left block over to the right block and drop it off inside.</p>\n";
    output+= "<div id=\"div1\" class=\"rectangle\">\n";
    output+= "<img src=\"images/green.png\" draggable=\"true\" ondragstart=\"drag(event)\" id=\"drag1\" class=\"rectangle\">\n";
    output+= "</div>\n";
    output+= "<div id=\"div2\" class=\"rectangle\" ondrop=\"drop(event)\" ondragover=\"allowDrop(event)\">\n";
    output+= "<img src=\"images/red.png\" id=\"drag2\" class=\"rectangle\">\n";
    output+= "</div>\n";
    output+= "</body>\n";
    output+= "<script type=\"text/javascript\" src=\"drag.js\"> </script>\n";
    sprintf(buffer, "<script> function nextStage() { console.log(Math.floor(new Date().getTime()/1000.0) + \".\" + new Date().getTime()%%1000 + \",drag,\" + %d + \"px,\" + %d + \"px\"); open(\"%s\", \"_self\"); } </script>\n", gapLength, rectWidth, &nextStage[0]);
    output+= buffer;
    output+= "</html>\n";
    free(buffer);

    return output;
}

int* generateRandomOrderArray(int num){
    int* output = (int*) malloc(num * sizeof(int));
    for (int i = 0; i < num; i++){
        output[i] = i;
    }
    random_shuffle(output, output + num - 1);
    for (int i = 0; i < num; i++){
        printf("%d\n", output[i]);
    }
    return output;
}
