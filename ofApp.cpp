#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	glm::vec3 point_base = glm::vec3(300 * cos((2 * ofGetFrameNum() % 360) * DEG_TO_RAD), 300 * sin((2 * ofGetFrameNum() % 360) * DEG_TO_RAD), 0);
	for (int v = 0; v < 360; v += 10) {

		for (int u = 0; u < 360; u += 20) {

			glm::vec3 point = glm::vec3(300 * cos(v * DEG_TO_RAD), 300 * sin(v * DEG_TO_RAD), 0);

			float r = 50;
			float noise_value = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01);
			float distance = glm::distance(point, point_base);
			if (distance < 200) {
				
				float noise_param = ofMap(distance, 200, 0, 0, 1);
				r += 150 * (noise_value * noise_param);
			}
			
			ofSetColor(39);
			ofFill();

			ofBeginShape();
			ofVertex(this->make_point(300, r, u - 10, v - 5));
			ofVertex(this->make_point(300, r, u + 10, v - 5));
			ofVertex(this->make_point(300, r, u + 10, v + 5));
			ofVertex(this->make_point(300, r, u - 10, v + 5));
			ofEndShape(true);

			ofSetColor(239);
			ofNoFill();

			ofBeginShape();
			ofVertex(this->make_point(300, r, u - 9.9, v - 4.9));
			ofVertex(this->make_point(300, r, u + 9.9, v - 4.9));
			ofVertex(this->make_point(300, r, u + 9.9, v + 4.9));
			ofVertex(this->make_point(300, r, u - 9.9, v + 4.9));
			ofEndShape(true);
		}
	}

	ofDrawSphere(point_base, 10);

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	float x = (R + r * cos(u)) * cos(v);
	float y = (R + r * cos(u)) * sin(v);
	float z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}