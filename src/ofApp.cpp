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
    frameRate = 30; // Framerate deseado
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
    loadSettingsFromXML("settings.xml");
    tipo.load("future-earth.ttf", tamTipo);

    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    uint64_t currentTime = ofGetElapsedTimeMillis();

    autorun();
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

    h=   images1[currentFrameIndex1].getHeight();
    h*= scale;
    w =   images1[currentFrameIndex1].getWidth();
    w*= scale;
    // Dibujar las imágenes en la pantalla

    if (images1 != nullptr) {
        images1[currentFrameIndex1].draw(posX, posY, w, h);
    }
    if (images2 != nullptr) {
        images2[currentFrameIndex2].draw(posX+w+gap, posY,  w, h);
    }
    if (images3 != nullptr) {
        images3[currentFrameIndex3].draw(posX+w*2.+gap*2., posY, w, h);
    }



    if(showDebug){
        int  bias,amp;
        float vel,peso,  velAcc;
        float velD, umbral;
        if(videoSelect==1){
            vel=vel1, bias=bias1, amp=amp1, peso=peso1, velD=velD1, umbral=umbral1;
            velAcc=velAcc1;

        }else if(videoSelect==2){
            vel=vel2, bias=bias2, amp=amp2, peso=peso2, velD=velD2, umbral=umbral2;
            velAcc=velAcc2;

        }else if(videoSelect==3){
            vel=vel3; bias=bias3, amp=amp3, peso=peso3, velD=velD3, umbral=umbral3;
            velAcc=velAcc3;

        }

        myfont.drawString("umbral dir(n m): "+to_string(umbral),50.,ofGetHeight()-100.);
        myfont.drawString("vel Dir (o l): "+to_string(velD),50.,ofGetHeight()-150.);
        myfont.drawString("peso (i k): "+to_string(peso),50.,ofGetHeight()-200.);
        myfont.drawString("amp fr(y h): "+to_string(amp),50.,ofGetHeight()-250.);
        myfont.drawString("bias fr(t g): "+to_string(bias),50.,ofGetHeight()-300.);
        myfont.drawString("vel noise(u j): "+to_string(vel),50.,ofGetHeight()-350.);
        myfont.drawString("velAcc(z x): "+to_string(velAcc),50.,ofGetHeight()-400.);


        myfont.drawString(to_string(currentFrameIndex1), posX, posY-15.);
        myfont.drawString(to_string(currentFrameIndex2),posX+w+gap, posY-15);
        myfont.drawString(to_string(currentFrameIndex3), posX+w*2.+gap*2. , posY-15);


        ofPushStyle();
        ofNoFill();
        ofSetColor(0,255.,0);
        if(videoSelect==1){
            ofDrawRectangle(posX, posY, w, h);
        }else  if(videoSelect==2){
            ofDrawRectangle(posX+w+gap, posY, w, h);
        }else  if(videoSelect==3){
            ofDrawRectangle(posX+w*2.+gap*2., posY, w, h);
        }
        ofPopStyle();
    }else{

        mascara.draw(0,0);
        ofPushMatrix();

         ofTranslate( ofGetWidth()/2.0,ofGetHeight()/2.0);
        // Rotar 90 grados para dibujar el texto en vertical
        ofRotateDeg(270);

        // Dibujar el texto en vertical
        float txt1 = float(currentFrameIndex1)/float(numImages1-1);
        float txt2 = float(currentFrameIndex2)/float(numImages2-1);
        float txt3 = float(currentFrameIndex3)/float(numImages3-1);
        tipo.drawString(ofToString(txt1, 2), posTxtX, posTxtY);
        tipo.drawString(ofToString(txt2, 2), posTxtX, posTxtY+gapTxt);
        tipo.drawString(ofToString(txt3, 2), posTxtX, posTxtY+gapTxt*2);

        // Restaurar la matriz original
        ofPopMatrix();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


    if( key == OF_KEY_BACKSPACE || key == OF_KEY_RETURN) showDebug= !showDebug;

    if (key == '0') {
        //  direction1 *= -1;
        videoSelect=0;
    }
    if (key == '1') {
        videoSelect=1;
    }
    if (key == '2') {
        videoSelect=2;
    }
    if (key == '3') {
        videoSelect=3;
    }
    if (key =='a' || key =='A') {
        posX--;

    }
    if (key =='q' || key =='Q') {
        // frameDuration1++; // Duración de cada frame en ms
        //if(frameDuration1>1000)frameDuration1=1000;
        scale-=0.01;
        if(scale<0.0)scale=.01;
    }
    if (key =='s' || key =='S') {
        posY++;
    }
    if (key =='w' || key =='W') {
        posY--;
    }
    if (key =='d' || key =='D') {
        posX++;
    }
    if (key =='e' || key =='E') {
        scale+=0.01;
        //if(scale>.0)scale=1.0;

    }
    if (key =='R' || key =='r') {
        gap++;

    }
    if (key =='F' || key =='f') {
        gap--;

    }

    if(!showDebug){
        if (key == OF_KEY_LEFT) {
            posTxtY -= 1; // Mover a la izquierda
        } else if (key == OF_KEY_RIGHT) {
            posTxtY += 1; // Mover a la derecha
        } else if (key == OF_KEY_UP) {
            posTxtX += 1; // Mover hacia arriba
        } else if (key == OF_KEY_DOWN) {
            posTxtX -= 1; // Mover hacia abajo
        }
        // Ajustar el gap con las teclas 'v' y 'b'
        if (key == 'v') {
            gapTxt -= 1; // Reducir el gap
        } else if (key == 'b') {
            gapTxt += 1 ;// Aumentar el gap
        }
    }
    //quizas no sea lo mas optimo pero me parecio mas prolijo que un select en cada tecla
    int  bias,amp;
    float vel,peso,velAcc;
    float velD, umbral;
    if(videoSelect==1){
        vel=vel1, bias=bias1, amp=amp1, peso=peso1, velD=velD1, umbral=umbral1;
        velAcc=velAcc1;
    }else if(videoSelect==2){
        vel=vel2, bias=bias2, amp=amp2, peso=peso2, velD=velD2, umbral=umbral2;
        velAcc=velAcc2;
    }else if(videoSelect==3){
        vel=vel3; bias=bias3, amp=amp3, peso=peso3, velD=velD3, umbral=umbral3;
        velAcc=velAcc3;
    }

    if (key =='Z' || key =='z') {
        velAcc+=0.005;
    }
    if (key =='x' || key =='X') {
        velAcc-=0.005;
    }
    if (key =='T' || key =='t') {
        bias++;
    }
    if (key =='g' || key =='g') {
        bias--;
    }
    if (key =='Y' || key =='y') {
        amp++;
    }
    if (key =='H' || key =='h') {
        amp--;
    }
    if (key =='U' || key =='u') {
        vel+=0.000005;
    }
    if (key =='J' || key =='j') {
        vel-=0.000005;
    }

    if (key =='I' || key =='i') {
        peso+=0.005;
    }
    if (key =='K' || key =='k') {
        peso-=0.005;
    }
    if(peso>1.f)peso=1.0f; if(peso<0.f)peso=0.05f;

    if (key =='O' || key =='o') {
        velD+=0.000005;
    }
    if (key =='L' || key =='l') {
        velD-=0.000005;
    }

    if (key =='n' || key =='N') {
        umbral+=0.005;
    }
    if (key =='m' || key =='M') {
        umbral-=0.005;
    }
    if(umbral>1.f)umbral=1.0f; if(umbral<0.f)umbral=0.005f;

    if(videoSelect==1){
        vel1=vel, bias1=bias, amp1=amp, peso1=peso, velD1=velD, umbral1=umbral;
        velAcc1=velAcc;

    }else if(videoSelect==2){
        vel2=vel, bias2=bias, amp2=amp, peso2=peso, velD2=velD, umbral2=umbral;
        velAcc2=velAcc;

    }else if(videoSelect==3){
        vel3=vel; bias3=bias, amp3=amp, peso3=peso, velD3=velD, umbral3=umbral;
        velAcc3=velAcc;
    }

    ofLog()<<"posX: "<<posX<<endl;
    ofLog()<<"posY: "<<posY<<endl;
    ofLog()<<"gap: "<<gap<<endl;
    ofLog()<<"scale: "<<scale<<endl;
    ofLog()<<"w: "<<w<<endl;
    ofLog()<<"h: "<<h<<endl;
    ofLog()<<"videoSelect: "<<videoSelect<<endl;
    ofLog()<<"bias: "<<bias<<endl;
    ofLog()<<"amp: "<<amp<<endl;
    ofLog()<<"vel: "<<vel<<endl;
    ofLog()<<"peso: "<<peso<<endl;
    ofLog()<<"velD: "<<velD<<endl;
    ofLog()<<"umbral: "<<umbral<<endl;

    saveSettingsToXML("settings.xml");


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
