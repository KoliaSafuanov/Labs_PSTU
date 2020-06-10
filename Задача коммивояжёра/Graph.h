#ifndef GRAPH_T
#define GRAPH_T
#include "glfunc.h"
#include <vector>
#include <iomanip>
#include <iostream>

extern bool* Mouse_Vert;
int COL, KommiRez = -1;
std::string  p;
class Graph; //�������� ������ 
void drawVertex(int n, Graph& graph); //�������� ������� drawVertex
int Circle_Check(int x, int y, Graph& graph); //�������� ������� Circle_Check
void mouseMove(int x, int y); //�������� ������� mouseMove

struct Edge{
  int from;
  int dest;
};

class Graph
{
private:
  std::vector<Edge> rez; //������ ����
  int **adjMatrix;//������� ���������
public:
  std::vector<std::string> vertList; //������ ������
  Graph() {this->InsertMatrix();}
  int GetAmountVerts() { return vertList.size(); }
  void InsertMatrix()//���� ������� � ����������
  {
    setlocale(LC_ALL, "ru");
    std::cout << "������� ���������� ������: ";std::cin >> COL;
    adjMatrix = new int* [COL];//������� ���������
    for (int i = 0; i < COL; i++) { adjMatrix[i] = new int[COL]; }
    std::cout << "������� " << COL << " ������: ";
    for (int i = 0; i < COL; i++)
    {
      std::string temp;
      std::cin >> temp;
      vertList.push_back(temp);
    }

    for (int i = 0; i < COL; i++)
    {
      for (int j = i; j < COL; j++)
      {
        if (i == j) adjMatrix[i][j] = -1;
        else
        {
          std::cout << "������� ��� ����� " << vertList[i] << " -> " << vertList[j] << ": ";
          std::cin >> adjMatrix[i][j];
          adjMatrix[j][i] = adjMatrix[i][j];
        }
      }
    }
    return;
  };

  void PrintMatrix(int** matrix) //������ �������
  {
    for (int i = 0; i < COL; i++)
    {
      std::cout << std::setw(2) << vertList[i] << ' ';
      for (int j = 0; j < COL; j++)
      {
        if (matrix[i][j] == -1) std::cout << "[] ";
        else std::cout << std::setw(2) << matrix[i][j] << ' ';
      }
      std::cout << std::endl;
    }
  };

  void RedRows(int** matrix) //�������� �����
  {
    for (int i = 0; i < COL; i++) //������ �� ��������
    {
      std::cout << std::setw(2) << vertList[i] << ' ';
      for (int j = 0; j < COL; j++)
      {
        if (matrix[i][j] == -1) std::cout << "[] ";
        else std::cout << std::setw(2) << matrix[i][j] << ' ';
      }
      std::cout << std::endl;
    }
  };

  void RedCols(int** map) //�������� ��������
  {
    for (int j = 0; j < COL; j++) //������ �� ��������
    {
      int min = INT32_MAX; //������� ��� ������� ������� ����������� ������

      for (int i = 0; i < COL; i++) //������ �� ������� �������
      {
        if ((map[i][j] < min) && (map[i][j] >= 0)) //���� ������ ������ �������� � �� �������� ���� � ��� �� �����
          min = map[i][j]; //��������� �������
      }

      for (int i = 0; i < COL; i++) //�������� �������
        if (map[i][j] != -1) //���� �� ���� � ��� �� �����
          map[i][j] -= min; //�������� �������
    }
  };

  int ZeroRows(int** map, int row, int nCheck) //������ ����� � �������
  {
    int min = INT32_MAX; // ������� ���������� ������������ ��������
    for (int j = 0; j < COL; j++) // �������� ������ ������� � �������� ������
      if (j != nCheck) // ���������� ������� �� ������� � ���������
        if ((min > map[row][j]) && (map[row][j] >= 0)) // ���� �������
          min = map[row][j]; // ��������� �������� ����������

    return min; // ���������� ����������� ��������
  };

  int ZeroCols(int** map, int nCheck, int col) //������ ����� � ��������
  {
    int min = INT32_MAX; //�������

    for (int i = 0; i < col; i++) //�������� ��� ������ � �������
      if (i != nCheck) //������ �� ������� � ��������
        if ((map[i][col] < min) && (map[i][col] >= 0)) //����� ��������
          min = map[i][col];

    return min;
  };

  Edge ClearMap(int** map) //�������� ������ � ������� � ���������� ����
  {
    Edge temp;

    int max = -1, k, l; //������������ ��������� ����, ���������� ��� ������ � �������

    for (int i = 0; i < COL; i++)
    {
      for (int j = 0; j < COL; j++)
      {
        if (map[i][j] == 0)
        {
          int tSum = this->ZeroRows(map, i, j) + this->ZeroCols(map, j, i);
          if (tSum >= max)
          {
            max = tSum;
            k = i;
            l = j;
          }
        }
      }
    }

    for (int i = 0; i < COL; i++)
      for (int j = 0; j < COL; j++)
      {
        if (i == k) map[i][j] = -1;
        if (j == l) map[i][j] = -1;
      }

    temp.from = k;
    temp.dest = l;

    return temp;
  };

  void Kommi() //�������� ������� ������ �����������
  {
    int col = COL;
    int** map = new int* [col];
    for (int i = 0; i < col; i++) map[i] = new int[col];

    for (int i = 0; i < col; i++)
      for (int j = 0; j < col; j++)
        map[i][j] = adjMatrix[i][j];

    int i = 0;
    while (i != col - 2) //�������� ����
    {
      RedRows(map);
      std::cout << i + 1 << ". �������� �����\n";
      PrintMatrix(map);

      RedCols(map);
      std::cout << i + 1 << ". �������� ��������\n";
      PrintMatrix(map);

      rez.push_back(ClearMap(map));

      std::cout << i + 1 << ". ����� �������\n";
      PrintMatrix(map);

      i++;
    }

  for (int i = 1; i < rez.size(); i++)
    {
      for (int j = i; j < rez.size(); j++)
        if (rez[i].from == rez[j].dest) std::swap(rez[i], rez[j]);
    }//�������� ����
    p += "Way: "+ vertList[rez[0].from] + " -> " + vertList[rez[0].dest] + " -> ";
    for (int i = 1; i < rez.size(); i++)
    {
      if (rez[i - 1].dest != rez[i].from) p += vertList[rez[i].from] + " -> " + vertList[rez[i].dest] + " -> ";
      else p += vertList[rez[i].dest] + " -> ";
    }
   
    {
      p += vertList[rez[0].from];
      std::string* s = new std::string;
      for (int i = 0; i < p.size(); i++)
      {
        *s += p[i];
      }
      p = *s;
      delete s;
    }
    std::cout << std::endl << p;

    int a = adjMatrix[rez[i - 1].dest][rez[0].from]; // ���������� �� ��������� ������� �� ������
    a += adjMatrix[rez[0].from][rez[0].dest]; // ���������� ������� �����

    for (int i = 1; i < rez.size(); i++) // �������� �� ������� ��������
      a += adjMatrix[rez[i].from][rez[i].dest]; // �������� ���������� i-���� ����� 

    for (int i = 0; i < rez.size() - 1; i++) // �������� �� ������� ��������
      if (rez[i].dest != rez[i + 1].from) // ���� ���� �����, �� ���������� �� ������� � �� � ������� ������ 0
        a += adjMatrix[rez[i].dest][rez[i + 1].from]; // ������� ���������� ����� ������� 

    std::cout << "\n����������: " << a << '\n';
    KommiRez = a;

    for (int i = 0; i < col; i++) delete[] map[i];
    delete[] map;
  }

  void DrawGraph()//��������� �����
  {

    int n = vertList.size();
    for (int i = 0; i < n; i++)
    {
      setCoord(i, n);//��������������� ����������
    }
    for (int i = 0; i < n; i++)
    {
      for (int j = 0 /*i + 1*/; j < n; j++)
      {
        int a = adjMatrix[i][j]; //a -- int, ������ ��� ��� ��� �����
        if (a > 0) //�� ������ ����� �� � � � (��� ����� -1)
        {
          drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y);
        }
      }
    }
    drawVertex(n, *this);
    if (KommiRez == -1) Kommi();
    drawRez(KommiRez, p);
  }
};

int Circle_Check(int x, int y, Graph& graph)//�������� ������� ������� � ����� - ������� �����
{
  for (int i = 0; i < graph.GetAmountVerts(); i++)
    if (pow(x - vertC[i].x, 2) + pow(y - vertC[i].y, 2) <= pow(R, 2))
      return i;
  return -1;
}
bool* Mouse_Vert = new bool[COL] ;

void drawVertex(int n, Graph& graph)//��������� ������ �����
{
  for (int i = 0; i < n; i++)
  {
    if (Mouse_Vert[i])//���� ������ ������, �� ����� ������
      drawBorderedCircle(vertC[i].x, vertC[i].y, R);
    else
      drawCircle(vertC[i].x, vertC[i].y, R);//����� - �������
    drawText(graph.vertList[i], vertC[i].x, vertC[i].y);
  }
}

#endif