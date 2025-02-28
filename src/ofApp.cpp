#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofLog()<<"setup"<<" :"<<"i"<<endl;

    //   ofSetFrameRate(60);
    ofSetWindowTitle("Video Frames Player");
    // Cargar imágenes desde las carpetas
    loadImagesFromFolder("img1", images1, numImages1);
      loadImagesFromFolder("img2", images2, numImages2);
      loadImagesFromFolder("img3", images3, numImages3);

    // Inicializar variables
    currentFrameIndex1 = 0;
    currentFrameIndex2 = 0;
    currentFrameIndex3 = 0;
    frameRate = 3; // Framerate deseado
    //esto individualizarlo y los timmers lo mismo
    frameDuration1 = 1000 / frameRate; // Duración de cada frame en ms
    lastFrameTime1 = ofGetElapsedTimeMillis();
    frameDuration2 = 1000 / frameRate; // Duración de cada frame en ms
    lastFrameTime2 = ofGetElapsedTimeMillis();
    frameDuration3 = 1000 / frameRate; // Duración de cada frame en ms
    lastFrameTime3 = ofGetElapsedTimeMillis();
    direction1 = direction2 = direction3 = 1; // 1 para adelante, -1 para reversa
    myfont.load("arial.ttf", 32);

    mascara.load("data/mascara_hd_rotada.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    uint64_t currentTime = ofGetElapsedTimeMillis();

    // Cambiar frames según el tiempo y la dirección
    if (currentTime - lastFrameTime1 >= frameDuration1) {
        updateFrame(currentFrameIndex1, numImages1, direction1);
        lastFrameTime1 = currentTime;
    }
    if (currentTime - lastFrameTime2 >= frameDuration2) {
        updateFrame(currentFrameIndex2, numImages2, direction2);
        lastFrameTime2 = currentTime;
    }
    if (currentTime - lastFrameTime3 >= frameDuration3) {
        updateFrame(currentFrameIndex3, numImages3, direction3);
        lastFrameTime3 = currentTime;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    // Dibujar las imágenes en la pantalla
     if (images1 != nullptr) {
         images1[currentFrameIndex1].draw(0, 0, ofGetWidth() / 3, ofGetHeight());
     }
     if (images2 != nullptr) {
         images2[currentFrameIndex2].draw(ofGetWidth() / 3, 0, ofGetWidth() / 3, ofGetHeight());
     }
     if (images3 != nullptr) {
         images3[currentFrameIndex3].draw(2 * ofGetWidth() / 3, 0, ofGetWidth() / 3, ofGetHeight());
     }

    if(showDebug){
    myfont.drawString(to_string(frameDuration3), 3*204.,ofGetHeight()/2-100.);
    myfont.drawString(to_string(frameDuration2), 2.*204,ofGetHeight()/2.-100);
    myfont.drawString(to_string(frameDuration1), 204 ,ofGetHeight()/2.-100);

    myfont.drawString(to_string(currentFrameIndex3), 3*204.,ofGetHeight()/2.);
    myfont.drawString(to_string(currentFrameIndex2), 2.*204,ofGetHeight()/2.);
    myfont.drawString(to_string(currentFrameIndex1), 204 ,ofGetHeight()/2.);
}else mascara.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


    if( key == OF_KEY_BACKSPACE || key == OF_KEY_RETURN) showDebug= !showDebug;

    if (key == '1') {
        direction1 *= -1;
    }
    if (key == '2') {
        direction2 *= -1;
    }
    if (key == '3') {
        direction3 *= -1;
    }
    if (key =='a' || key =='A') {

        frameDuration1--; // Duración de cada frame en ms
        if(frameDuration1<1)frameDuration1=1;

    }
    if (key =='q' || key =='Q') {
        frameDuration1++; // Duración de cada frame en ms
        if(frameDuration1>1000)frameDuration1=1000;
    }

    if (key =='s' || key =='S') {

        frameDuration2--; // Duración de cada frame en ms
        if(frameDuration2<1)frameDuration2=1;

    }
    if (key =='w' || key =='W') {
        frameDuration2++; // Duración de cada frame en ms
        if(frameDuration2>1000)frameDuration2=1000;
    }

    if (key =='d' || key =='D') {

        frameDuration3--; // Duración de cada frame en ms
        if(frameDuration3<1)frameDuration3=1;

    }
    if (key =='e' || key =='E') {
        frameDuration3++; // Duración de cada frame en ms
        if(frameDuration3>1000)frameDuration3=1000;
    }


}

void ofApp::freeImages(ofImage*& images, int numImages) {
    if (images != nullptr) {
        delete[] images; // Liberar memoria
        images = nullptr;
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    // Liberar memoria al salir
    freeImages(images1, numImages1);
    freeImages(images2, numImages2);
    freeImages(images3, numImages3);
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
