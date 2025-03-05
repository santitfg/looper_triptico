#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"


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

    float scale= 1.0;
    float posX = 118 ;
    float posY = 105 ;
    float gap = 104;//distancia entre imgs
    float h, w;
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


    void saveSettingsToXML(const string& filename) {
        ofxXmlSettings xml;

        // Crear un nodo raíz llamado "settings"
        xml.addTag("settings");
        xml.pushTag("settings");

        // Agregar los valores como etiquetas
        xml.addValue("scale", scale);
        xml.addValue("posX", posX);
        xml.addValue("posY", posY);
        xml.addValue("gap", gap);
        xml.addValue("height", h);
        xml.addValue("width", w);

        // Guardar el archivo XML
        if (xml.saveFile(filename)) {
            ofLogNotice() << "Settings saved to " << filename;
        } else {
            ofLogError() << "Failed to save settings to " << filename;
        }
    }

    void loadSettingsFromXML(const string& filename) {
        ofxXmlSettings xml;

        // Cargar el archivo XML
        if (xml.loadFile(filename)) {
            // Moverse al nodo raíz "settings"
            if (xml.tagExists("settings")) {
                xml.pushTag("settings");

                // Leer los valores y asignarlos a las variables globales
                scale = xml.getValue("scale", 1.0); // Valor por defecto 1.0
                posX = xml.getValue("posX", 118.0); // Valor por defecto 118.0
                posY = xml.getValue("posY", 105.0); // Valor por defecto 105.0
                gap = xml.getValue("gap", 104.0);   // Valor por defecto 104.0
                h = xml.getValue("height", 0.0);    // Valor por defecto 0.0
                w = xml.getValue("width", 0.0);     // Valor por defecto 0.0

                xml.popTag(); // Salir del nodo "settings"

                ofLogNotice() << "Settings loaded from " << filename;
            } else {
                ofLogError() << "Invalid XML structure in " << filename;
            }
        } else {
            ofLogError() << "Failed to load settings from " << filename;
        }
    }

    void autorun(){
        float vel=0.001;// 1 seg/1micro
       float  umbral =0.5;
       float t =ofGetElapsedTimeMillis()*vel; // o  double o realizar la conversion en la func
        direction1= (ofNoise(t)>=umbral) ?1:-1;
        direction2= (ofNoise(t)>=umbral) ?1:-1;
        direction3= (ofNoise(t)>=umbral) ?1:-1;

        int bias= 42;
        int amp=30;
        float peso=0.5;
        t =ofGetElapsedTimeMillis()*0.001; //
        frameDuration1 = ((sin(t +sin(t*0.005)))*0.5+0.5)*peso + (1.0-peso)*ofNoise(t))*amp+bias;
        frameDuration2 = ((sin(t *sin(t)))*0.5+0.5)*peso + (1.0-peso)*ofNoise(t))*amp+bias;
        frameDuration3 = ((sin(t )*0.5+0.5)*peso + (1.0-peso)*ofNoise(t))*amp+bias;
    }
};
