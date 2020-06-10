#include <iostream>
#include "Graph.h"
#include <string>
#include <Windows.h>

using namespace std;
Graph graph;//Создание объекта класса Graph
int CursorX, CursorY;//Глобальные переменные, отвечающие за положение курсора

void reshape(int w, int h) //Функция, отвечающая за масштабируемость изображения
{
  WinW = w;
  WinH = h;
  glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
  glutPostRedisplay();
}
void mouseMove(int x, int y)//Функция, отвечающая за нахождение координат курсора
{
  y = WinH - y;
  CursorX = x;
  CursorY = y;
  int i = Circle_Check(x, y, graph);
  if (i != -1)
    Mouse_Vert[i] = true;
  else
    for (int j = 0; j < graph.GetAmountVerts(); j++)
      Mouse_Vert[j] = false;
  glutPostRedisplay();
}

void display()//Функция, отвечающая за  изображение
{
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, WinW, 0, WinH); //Установка начала координат (нижний левый угол)
  glViewport(0, 0, WinW, WinH);
  glClearColor(1.0f, 0.5f, 0.0f, 0.0f);//Задание цвета экрана
  glClear(GL_COLOR_BUFFER_BIT);
  graph.DrawGraph();//Вызов функции отрисовки графа
  glutSwapBuffers();
}

int main(int argc, char* argv[])
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(1300, 720);//Масштаб окна Open Gl
  glutCreateWindow("Задача коммивояжёра");
  WinW = glutGet(GLUT_WINDOW_WIDTH);
  WinH = glutGet(GLUT_WINDOW_HEIGHT);
  glutDisplayFunc(display); //Вывод изображения
  glutReshapeFunc(reshape); //Масштабируемость изображения
  glutPassiveMotionFunc(mouseMove);//Положение курсора 
  glutMainLoop();

  return 0;
}

