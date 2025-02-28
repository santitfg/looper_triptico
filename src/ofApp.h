#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofImage* images1 = nullptr;
    ofImage* images2 = nullptr;
    ofImage* images3 = nullptr;
    int numImages1 = 0, numImages2 = 0, numImages3 = 0;

    ofImage mascara;
    //vector<ofImage> images1, images2, images3;
    int currentFrameIndex1, currentFrameIndex2, currentFrameIndex3;
    int frameRate;
    int frameDuration1,frameDuration2,frameDuration3;
    uint64_t lastFrameTime1,lastFrameTime2,lastFrameTime3;
    int direction1, direction2, direction3;
    ofTrueTypeFont myfont;

    bool showDebug = false;
    void freeImages(ofImage*& images, int numImages);

    void loadImagesFromFolder(const string& folderPath, ofImage*& images, int& numImages){
        ofDirectory dir(folderPath);
        dir.allowExt("png");
        dir.allowExt("jpg");
        dir.listDir();
        dir.sort();

        numImages = dir.size();
        images = new ofImage[numImages]; // Asignar memoria para el array

        for (int i = 0; i < numImages; i++) {
            images[i].load(dir.getPath(i));
            ofLog() << dir.getPath(i) << endl;
        }

    }

    void updateFrame(int& currentFrameIndex, int totalFrames, int& direction) {
        currentFrameIndex += direction;

        if (currentFrameIndex >= totalFrames) {
            currentFrameIndex = 0; // Loop
        } else if (currentFrameIndex < 0) {
            currentFrameIndex = totalFrames - 1; // Reversa
        }
    }
};
