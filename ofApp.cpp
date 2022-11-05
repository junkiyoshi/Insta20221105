#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.666666666666 * 2);

	int v_span = 2;
	int u_span = 20;
	int R = 200;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	
	for (int v = 0; v < 360; v += v_span) {

		for (int u = 0; u < 360; u += u_span) {

			auto noise_value = ofNoise(glm::vec4(this->make_point(R, 10, u, v) * 0.025, ofGetFrameNum() * 0.045));
			auto r = noise_value > 0.55 ? ofMap(noise_value, 0.55, 1, 40, 160) : 40;

			face.addVertex(this->make_point(R, r, u, v));
			face.addVertex(this->make_point(R, r, u + u_span, v));
			face.addVertex(this->make_point(R, r, u + u_span, v + v_span));
			face.addVertex(this->make_point(R, r, u, v + v_span));

			line.addVertex(this->make_point(R, r, u, v));
			line.addVertex(this->make_point(R, r, u + u_span, v));
			line.addVertex(this->make_point(R, r, u + u_span, v + v_span));
			line.addVertex(this->make_point(R, r, u, v + v_span));

			ofColor face_color = ofColor(0);
			ofColor line_color = ofColor(255, 0, 255);

			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);

			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);

			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
			line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
			line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);

		}
	}

	face.drawFaces();
	line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}