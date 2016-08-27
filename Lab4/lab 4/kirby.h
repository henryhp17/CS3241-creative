#ifndef KIRBY_H
#define KIRBY_H

void drawCircle(float radius);
void drawOutlineCircle(float in_radius, float out_radius);
void drawRectangle(float length, float width);
void drawOutline(float length, float width);
void drawEllipse(float xradius, float yradius);
void drawGradientEllipse(float xradius, float yradius);
void drawOutlineEllipse(float in_xradius, float in_yradius, float out_xradius, float out_yradius);
void drawOutlineRightHand(float in_xradius, float in_yradius, float out_xradius, float out_yradius);
void drawKirbyFoot();
void drawKirbyEyes();
void drawKirbyTongue(float xradius, float yradius);
void drawKirby();

#endif