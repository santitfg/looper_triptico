#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

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


    vector<ofImage> images1, images2, images3;
    int currentFrameIndex1, currentFrameIndex2, currentFrameIndex3;
    int frameRate;
    int frameDuration1,frameDuration2,frameDuration3;
    uint64_t lastFrameTime1,lastFrameTime2,lastFrameTime3;
    int direction1, direction2, direction3;
    ofTrueTypeFont myfont;

    bool showDebug = false;

    void loadImagesFromFolder(const string& folderPath, vector<ofImage>& images) {
        ofDirectory dir(folderPath);
        dir.allowExt("png");
        dir.allowExt("jpg");
        dir.listDir();
        dir.sort();

        for (int i = 0; i < dir.size(); i++) {
            ofImage img;
//            ofLog()<<folderPath<<" :"<<i<<endl;
          ofLog()<<dir.getPath(i)<<endl;
            img.load(dir.getPath(i));
            images.push_back(img);
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
