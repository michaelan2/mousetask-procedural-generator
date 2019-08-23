//
//  main.cpp
//  generateTasks
//
//  Created by Michael An on 8/21/19.
//  Copyright © 2019 Michael An. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

string mSteer(int rectWidth, int rectHeight, int gapLength, int gapHeight, string nextStage);
string mClick(int rectWidth, int rectHeight, int gapLength, string nextStage);
string mDrag(int rectWidth, int rectHeight, int gapLength, string nextStage);


int main(int argc, const char * argv[]) {
    // insert code here...
    string test = "test";
    test += "\n";
    cout << "Hello, World!\n";
    //printf(&test[0]);
    cout << mDrag(100, 200, 20, "mousedraw.html");
    int nums[] = {1, 2, 3, 4, 5, 6, 7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
    int currentnum = 0;
    
    int l = 64;
    int w = 8;
    for (int l = 64; l < 128 + 1; l*= 2){
        for (int w = 8; w < 32 + 1; w*=2){
            char* curr = (char*) malloc(100);
            char* next = (char*) malloc(100);
            sprintf(curr, "%d.html", nums[currentnum]);
            sprintf(next, "%d.html", nums[currentnum+1]);
            FILE* steer = fopen(curr, "w");
            fprintf(steer, "%s", &mSteer(l, 100, l, w, next)[0]);
            currentnum++;
            sprintf(curr, "%d.html", nums[currentnum]);
            sprintf(next, "%d.html", nums[currentnum+1]);
            FILE* click = fopen(curr, "w");
            fprintf(click, "%s", &mClick(w, 100, l, next)[0]);
            currentnum++;
            sprintf(curr, "%d.html", nums[currentnum]);
            sprintf(next, "%d.html", nums[currentnum+1]);
            FILE* drag = fopen(curr, "w");
            fprintf(drag, "%s", &mDrag(w, 100, l, next)[0]);
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
    output+= "<p> Move to the left zone, click and hold to draw, and draw a line to the right zone without touching the walls </p>\n";
    output+= "<div id=\"div1\">\n";
    output+= "<img id=\"click1\" src=\"images/black.png\" class=\"rectangle\">\n";
    output+= "</div>\n";
    output+= "<div id=\"div2\">\n";
    output+= "<img id=\"click2\" src=\"images/black.png\" class=\"rectangle\">\n";
    output+= "<script>\n";
    output+= "function nextStage() {\n";
    sprintf(buffer, "if (currX > 0.5*(canvas.width + %d)) {open(\"%s\", \"_self\") }}", rectWidth, &nextStage[0]);
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
    sprintf(buffer, "document.getElementById('click2').onclick = function nextStage() { open(\"%s\", \"_self\"); }\n", &nextStage[0]);
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
    output+= "<div id=\"div1\" class=\"rectangle\" ondrop=\"drop(event)\" ondragover=\"allowDrop(event)\">\n";
    output+= "<img src=\"images/green.png\" draggable=\"true\" ondragstart=\"drag(event)\" id=\"drag1\" class=\"rectangle\">\n";
    output+= "</div>\n";
    output+= "<div id=\"div2\" class=\"rectangle\" ondrop=\"drop(event)\" ondragover=\"allowDrop(event)\">\n";
    output+= "<img src=\"images/red.png\" id=\"drag2\" class=\"rectangle\">\n";
    output+= "</div>\n";
    output+= "</body>\n";
    output+= "<script type=\"text/javascript\" src=\"drag.js\"> </script>\n";
    sprintf(buffer, "<script> function nextStage() { open(\"%s\", \"_self\"); } </script>\n", &nextStage[0]);
    output+= buffer;
    output+= "</html>\n";
    free(buffer);

    return output;
}


