#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup() {
    sound.load("beat.wav");            // Loads a sound file (in bin/data/)
    sound.setLoop(true);              // Makes the song loop indefinitely
    sound.setVolume(1);               // Sets the song volume
    ofSetBackgroundColor(51, 255, 153); // Sets the Background Color
}
//--------------------------------------------------------------
void ofApp::update() {
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    if(!pause && not_dragging){                     //Sets the condition for the press 'a' to pause visualizer key
    ofSoundUpdate();               // Updates all sound players
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    progress = sound.getPosition();
    progBar=progress*ofGetWidth();
    }
    if (loop == true && progress >= 0.99) {
        song_playing++; // Move to the next song
        if (song_playing >= playlist.size()) {
            if (loop) {
                song_playing = 0; // Loop back to the first song
            } else {
                sound.stop(); // Stop playing if looping is disabled
            }
        }
        if (sound.isPlaying()) {
            sound.stop(); // Stop the current song
        }
        
        // Load and play the next song
        sound.load(playlist[song_playing]);
        sound.play();
    }  
    if(repeat&&progress>=0.99){
        sound.stop();
        sound.play();
    }
    if (shuffle && progress>=0.99){             //Sets the conditions for the shuffle key to work
        sound.stop();
        random_song= std::rand()%playlist.size();
        sound.load(playlist[random_song]);
        sound.play();
    }
    }
//--------------------------------------------------------------
void ofApp::draw() {
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofSetColor(256);
    ofFill();
    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);
    ofSetColor(0,ofRandom(0,255),0);
    ofDrawRectangle(0,40,progBar,20);
    // Mode Selection
    if (!playing) {
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1') {
        drawMode1(amplitudes);
    } else if (mode == '2') {
        drawMode2(amplitudes);
    } else if (mode == '3') {
        drawMode3(amplitudes);
    }

    ofSetColor(255);
    if (loop) {
        ofDrawBitmapString("Loop mode is on", 10, 80);
    }
    if (shuffle) {
        ofDrawBitmapString("Shuffle mode is on", 10, 80);
    }
    if (repeat) {
        ofDrawBitmapString("Repeat mode is on", 10, 80);
    }
}


// ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);
void ofApp::drawMode1(vector<float> amplitudes) {
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetBackgroundColor(51, 255, 153);
    ofColor blue= ofColor( 0 ,0,ofRandom(0,255)); //creates a random shade of blue
    ofSetColor(blue);
    rect_num=amplitudes.size();
    for(int i=0; i<rect_num; i++ ){         
    ofDrawRectRounded(i*ofGetWidth()/rect_num, ofGetHeight()-20, ofGetWidth()/rect_num , amplitudes[i]*7.5,15); //creates multiple rectangles that respond to different values of the amplitude parameter
    }
}
void ofApp::drawMode2(vector<float> amplitudes) {
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    ofSetBackgroundColor(117,30, 201); //Sets the background color
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
}
void ofApp::drawMode3(vector<float> amplitudes){
    ofSetBackgroundColor(1,2,3);
    ofPushStyle();
    ofSetColor(255);
    ofSetLineWidth(2);
    float bandWidth = ofGetWidth() / (float)amplitudes.size();
    float halfHeight = ofGetHeight() / 2.0f;
    // Draw the frequency wave
    ofPolyline line;
    for(auto amplitude : amplitudes){
        float y = amplitude * halfHeight;
        // Use sine function to make smoother wave
        y = sin(y) * halfHeight;
        line.addVertex(line.size() * bandWidth, halfHeight + y);
    }
    line.draw();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // This method is called automatically when any key is pressed
    switch (key) {
    case 'p':
        if (playing) {
            sound.stop();
        } else {
            sound.play();
        }
        playing = !playing;
        break;
    case '1':
        mode = '1';
        break;
    case '2':
        mode = '2';
        break;
    case '3':
        mode = '3';
        break;
    case 'g':
            sound.load("geesebeat.wav");
            sound.play();
         break;
    case 'c':
            sound.load("pigeon-coo.wav");
            sound.play();
            break;
    case 'u':
            sound.load("rock-song.wav");
            sound.play();
            break;
    case 'd':
            sound.load("DukiBiza.mp3");
            sound.play();
            break;
    case 'e':
        sound.load("Gladiador.mp3");
        sound.play();
        break;
    case 's':
        sound.load("SinFrenos.mp3");
        sound.play();
        break;
    case 'q':
        sound.load("QuevedoBiza.mp3");
        sound.play();
        break;
    case 'w':
        sound.load("DieForYou.mp3");
        sound.play();
        break;
    case 'o':
        sound.load("OjitosLindos.mp3");
        sound.play();
        break;
    case 'm':
        sound.load("COMOHASESTAU.mp3");
        sound.play();
        break;
    case 'a':                           //Pauses visualizer
        pause=!pause;
        break;
    case '=':                           //Raises the volume
        sound.setVolume(min(sound.getVolume()+0.01,1.0));
        break;
    case '-':                           //Lowers the volume
        sound.setVolume(max(sound.getVolume()-0.01,0.0));
        break;  
    case 'l':
        loop=!loop;
        shuffle=false;
        repeat=false;
        break;

    case 'r':
           repeat=!repeat;
           shuffle=false;
           loop=false;
            // toggle the repeat mode on/off
            break;

     case 'b':
                shuffle=!shuffle; //Toggles the shuffle mode on/off and sets repeat mode and loop mode to false
                repeat=false;
                loop=false;
            break;
            }
    }
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    cur_x = x;
    cur_y = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if (y >= 40 && y <= 40 + 20) {
        float percentage_played = (float)(x - 0) / progBar;
        sound.setPosition(percentage_played * sound.getPosition());
    }
}

void ofApp::mouseDragged(int x, int y, int button) {
    if (y >= 40 && y <= 40 + 20) {
        percentage_played = (float)(x - 0) / progBar;
        sound.setPosition(percentage_played * sound.getPosition());
    }
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
//--------------------------------------------------------------