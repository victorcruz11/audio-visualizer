#pragma once

#include "AudioVisualizer.hpp"
#include "ofMain.h"

class ofApp : public ofBaseApp {

  private:
    ofSoundPlayer sound;
    AudioVisualizer visualizer;
    bool playing = false;
    char mode = '1';
    int cur_x, cur_y = 0;
    float sound_length;
    float progress = 0;
    float lastPos = 0;
    vector<string> playlist = {"beat.wav", "COMOHASESTAU.mp3", "DieForYou.mp3", "DukiBiza.mp3", "Gladiator.mp3", "geesebeat.wav", "OjitosLindos.mp3", "pigeon-coo.wav", "QuevedoBiza.mp3", "rock-song.wav", "sinFrenos.mp3"};
    int song_playing = 0;
  public:
    bool pause= false;
    int rect_num;
    int point=2;
    float progBar;
    int random_song;
    float percentage_played;
    bool not_dragging= true;
    bool repeat= false;
    bool shuffle= false;
    bool loop= false;
    void setup();
    void update();
    void draw();
    void drawMode1(vector<float> amplitudes);
    void drawMode2(vector<float> amplitudes);
    void drawMode3(vector<float> amplitudes);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
