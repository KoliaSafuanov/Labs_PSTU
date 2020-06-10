#ifndef GLFUNC_H
#define GLFUNC_H
#include <string>
#include <GL/glut.h>
#include <cmath>
#include <vector>

int WinW, WinH, R;//Глобальные переменные, задающие начало координат и радиус окружности соответственно

struct vertCoord //Координаты вершины графа
{
	int x, y;
};
vertCoord vertC[20];

void setCoord(int i, int n) { //Функция  устанавливает координаты для вершин графа
	int R_;
	int x0 = WinW / 2;
	int y0 = WinH / 2;
	if (WinW > WinH)
	{
		R = 5 * (WinH / 13) / n;
		R_ = WinH / 2 - R - 10;
	}
	else {
		R = 5 * (WinW / 13) / n;
		R_ = WinW / 2 - R - 10;
	}
	float theta = 2.0f * 3.1415926f * float(i) / float(n);
	float y1 = R_ * cos(theta) + y0;
	float x1 = R_ * sin(theta) + x0;

	vertC[i].x = x1;
	vertC[i].y = y1;
}

void drawCircle(int x, int y, int R) {//Функция рисует круг в заданных координатах

	glColor3f(1.0, 0.0, 0.0);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawBorderedCircle(int x, int y, int R)
{
	glColor3f(255, 165, 0);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0, 0, 0);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawText(std::string nom, int x1, int y1){ //Функция  размещает текст по заданным координатам
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	std::string s = nom;
	glRasterPos2i(x1 - 5, y1 - 5);
	for (int j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);//Текст выводится 
}

void drawRez(int KommiRez, std::string rez){//Функция  размещает текст по заданным координатам
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	std::string a = "Result: ";
	glRasterPos2i(WinW - 430, WinH - 50);
	for (int j = 0; j < a.length(); j++)
		glutBitmapCharacter(font, a[j]);//Текст выводится 

	std::string r = std::to_string(KommiRez);
	glRasterPos2i(WinW - 360, WinH - 50);
	for (int j = 0; j < r.length(); j++)
		glutBitmapCharacter(font, r[j]);//Текст выводится 

	glRasterPos2i(WinW - 430, WinH - 100);
	for (int j = 0; j < rez.length(); j++)
		glutBitmapCharacter(font, rez[j]);//Текст выводится 
}

void drawLine(int a, int x0, int y0, int x1, int y1) { //Отрисовка ребра ориентированного взвешенного графа
	glColor3i(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();
	drawText(std::to_string(a), (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);

	float vx = x0 - x1;
	float vy = y0 - y1;
	float s = 1.0f / sqrt(vx * vx + vy * vy);
	vx *= s;
	vy *= s;
	x1 = x1 + R * vx;
	y1 = y1 + R * vy;

	glColor3i(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x1 + 10 * (vx + vy), y1 + 10 * (vy - vx));
	glVertex2f(x1 + 10 * (vx - vy), y1 + 10 * (vy + vx));
	glEnd();
}
#endif