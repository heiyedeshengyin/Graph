/*
	Copyright 2019 heiyedeshengyin All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include "graph.h"

namespace hjr {

template <typename Tv, typename Te>
graph<Tv, Te>::graph()
{
	ver_num = 0;
	edge_num = 0;
	V = nullptr;
	E = nullptr;
}

template <typename Tv, typename Te>
graph<Tv, Te>::graph(bool isInit)
{
	if (isInit)
	{
		std::cout << "请输入结点的数目:";
		int ver;
		std::cin >> ver;

		if (ver > 0)
		{
			ver_num = ver;
			std::cout << "输入成功,总共有" << ver_num << "个结点" << std::endl;
			V = new vertex<Tv> * [ver_num];
			for (int i = 0; i < ver_num; i++)
			{
				std::cout << "请输入" << i << "号(第" << i + 1 << "个)结点的信息:";
				Tv v_data;
				std::cin >> v_data;
				V[i] = new vertex<Tv>(v_data);
			}
			std::cout << "结点输入完毕!" << std::endl << std::endl;

			edge_num = 0;
			E = new edge<Te> * *[ver_num];
			for (int i = 0; i < ver_num; i++)
				E[i] = new edge<Te> * [ver_num];
			for (int i = 0; i < ver_num; i++)
				for (int j = 0; j < ver_num; j++)
				{
					std::cout << "是否从" << i << "号结点(信息:" << V[i] -> data << ")到" << j << "号结点(信息:" << V[j] -> data << ")构造一条边[y/n]:";
					char str;
					std::cin >> str;
					if (str == 'y')
					{
						std::cout << "构建成功,请输入该边的信息:";
						Te e_data;
						std::cin >> e_data;
						std::cout << "请输入该边的权重:";
						int _weight;
						std::cin >> _weight;
						E[i][j] = new edge<Te>(e_data, _weight);
						edge_num++;
						V[i] -> out_degree++;
						V[j] -> in_degree++;
					}
					else
						E[i][j] = nullptr;
				}
			std::cout << "边输入完毕!" << std::endl << std::endl;
		}
		else
		{
			std::cout << "输入的值不是正数,不符合要求" << std::endl << std::endl;
			ver_num = 0;
			edge_num = 0;
			V = nullptr;
			E = nullptr;
		}
	}
	else
	{
		ver_num = 0;
		edge_num = 0;
		V = nullptr;
		E = nullptr;
	}
}

template <typename Tv, typename Te>
graph<Tv, Te>::graph(const graph& ano)
{
	ver_num = ano.ver_num;
	edge_num = ano.edge_num;
	if (ver_num > 0)
	{
		V = new vertex<Tv> * [ver_num];
		for (int i = 0; i < ver_num; i++)
		{
			V[i] = new vertex<Tv>(ano.V[i]->data);
			V[i]->in_degree = ano.V[i]->in_degree;
			V[i]->out_degree = ano.V[i]->out_degree;
		}

		E = new edge<Te> * *[ver_num];
		for (int i = 0; i < ver_num; i++)
			E[i] = new edge<Te> * [ver_num];
		for (int i = 0; i < ver_num; i++)
			for (int j = 0; j < ver_num; j++)
				if (ano.E[i][j])
					E[i][j] = new edge<Te>(ano.E[i][j]->data, ano.E[i][j]->weight);
				else
					E[i][j] = nullptr;
	}
	else
	{
		V = nullptr;
		E = nullptr;
	}
}

template <typename Tv, typename Te>
graph<Tv, Te>::~graph()
{
	for (int i = 0; i < ver_num; i++)
		for (int j = 0; j < ver_num; j++)
			if (E[i][j])
				delete E[i][j];

	for (int i = 0; i < ver_num; i++)
	{
		delete[] E[i];
		delete V[i];
	}

	delete[] E;
	delete[] V;
}

template <typename Tv, typename Te>
Tv graph<Tv, Te>::get_ver_data(int i)
{
	if (i >= 0 && i < ver_num)
		return V[i]->data;
	else
		return NULL;
}

template <typename Tv, typename Te>
int graph<Tv, Te>::get_ver_indegree(int i)
{
	if (i >= 0 && i < ver_num)
		return V[i]->in_degree;
	else
		return -1;
}

template <typename Tv, typename Te>
int graph<Tv, Te>::get_ver_outdegree(int i)
{
	if (i >= 0 && i < ver_num)
		return V[i]->out_degree;
	else
		return -1;
}

template <typename Tv, typename Te>
Tv graph<Tv, Te>::update_ver_data(int i, Tv _data)
{
	if (i >= 0 && i < ver_num)
	{
		Tv _return = V[i]->data;
		V[i]->data = _data;
		return _return;
	}
	else
		return NULL;
}

template <typename Tv, typename Te>
int graph<Tv, Te>::update_ver_indegree(int i, int _indegree)
{
	if (i >= 0 && i < ver_num)
	{
		int _return = V[i]->in_degree;
		V[i]->in_degree = _indegree;
		return _return;
	}
	else
		return -1;
}

template <typename Tv, typename Te>
int graph<Tv, Te>::update_ver_outdegree(int i, int _outdegree)
{
	if (i >= 0 && i < ver_num)
	{
		int _return = V[i]->out_degree;
		V[i]->out_degree = _outdegree;
		return _return;
	}
	else
		return -1;
}

template <typename Tv, typename Te>
int graph<Tv, Te>::insert_ver(Tv _data)
{
	if (ver_num > 0)
	{
		ver_num++;
		vertex<Tv>** new_V;
		new_V = new vertex<Tv> * [ver_num];
		for (int i = 0; i < ver_num - 1; i++)
		{
			new_V[i] = new vertex<Tv>(V[i]->data);
			new_V[i]->in_degree = V[i]->in_degree;
			new_V[i]->out_degree = V[i]->out_degree;
		}
		new_V[ver_num - 1] = new vertex<Tv>(_data);

		for (int i = 0; i < ver_num - 1; i++)
			delete V[i];
		delete[] V;
		V = new_V;

		edge<Te>*** new_E;
		new_E = new edge<Te> * *[ver_num];
		for (int i = 0; i < ver_num; i++)
			new_E[i] = new edge<Te> * [ver_num];
		for (int i = 0; i < ver_num; i++)
			for (int j = 0; j < ver_num; j++)
				if (i < ver_num - 1 && j < ver_num - 1)
				{
					if (E[i][j])
						new_E[i][j] = new edge<Te>(E[i][j]->data, E[i][j]->weight);
					else
						new_E[i][j] = nullptr;
				}
				else
					new_E[i][j] = nullptr;
		for (int i = 0; i < ver_num - 1; i++)
			for (int j = 0; j < ver_num - 1; j++)
				delete E[i][j];
		for (int i = 0; i < ver_num - 1; i++)
			delete[] E[i];
		delete[] E;
		E = new_E;

		return ver_num - 1;
	}
	else
	{
		ver_num = 1;
		V = new vertex<Tv> * [1];
		E = new edge<Te> * *[1];
		E[0] = new edge<Te> * [1];
		V[0] = new vertex<Tv>(_data);
		E[0][0] = nullptr;

		return 0;
	}
}

template <typename Tv, typename Te>
Tv graph<Tv, Te>::remove_ver(int i)
{
	if (i >= 0 && i < ver_num && ver_num > 1)
	{
		ver_num--;
		vertex<Tv>** new_V;
		new_V = new vertex<Tv> * [ver_num];
		for (int j = 0; j < i; j++)
			new_V[j] = new vertex<Tv>(V[j]->data);
		for (int j = i; j < ver_num; j++)
			new_V[j] = new vertex<Tv>(V[j + 1]->data);
		Tv vBack = V[i]->data;

		for (int j = 0; j < ver_num + 1; j++)
			delete V[j];
		delete[] V;
		V = new_V;

		edge_num = 0;
		edge<Te>*** new_E;
		new_E = new edge<Te> * *[ver_num];
		for (int j = 0; j < ver_num; j++)
			new_E[j] = new edge<Te> * [ver_num];
		for (int j = 0; j < i; j++)
		{
			for (int k = 0; k < i; k++)
			{
				if (E[j][k])
				{
					new_E[j][k] = new edge<Te>(E[j][k]->data, E[j][k]->weight);
					V[j]->out_degree++;
					V[k]->in_degree++;
					edge_num++;
				}
				else
					new_E[j][k] = nullptr;
			}
			for (int k = i; k < ver_num; k++)
			{
				if (E[j][k + 1])
				{
					new_E[j][k] = new edge<Te>(E[j][k + 1]->data, E[j][k + 1]->weight);
					V[j]->out_degree++;
					V[k]->in_degree++;
					edge_num++;
				}
				else
					new_E[j][k] = nullptr;
			}
		}
		for (int j = i; j < ver_num; j++)
		{
			for (int k = 0; k < i; k++)
			{
				if (E[j + 1][k])
				{
					new_E[j][k] = new edge<Te>(E[j + 1][k]->data, E[j + 1][k]->weight);
					V[j]->out_degree++;
					V[k]->in_degree++;
					edge_num++;
				}
				else
					new_E[j][k] = nullptr;
			}
			for (int k = i; k < ver_num; k++)
			{
				if (E[j + 1][k + 1])
				{
					new_E[j][k] = new edge<Te>(E[j + 1][k + 1]->data, E[j + 1][k + 1]->weight);
					V[j]->out_degree++;
					V[k]->in_degree++;
					edge_num++;
				}
				else
					new_E[j][k] = nullptr;
			}
		}

		for (int j = 0; j < ver_num + 1; j++)
			for (int k = 0; k < ver_num + 1; k++)
				delete E[j][k];
		for (int j = 0; j < ver_num + 1; j++)
			delete[] E[j];
		delete[] E;
		E = new_E;

		return vBack;
	}
	else if (i >= 0 && i < ver_num && ver_num == 1)
	{
		Tv vBack = V[0]->data;
		ver_num = 0;
		edge_num = 0;
		delete V[0];
		delete[] V;
		V = nullptr;
		if(E[0][0])
			delete E[0][0];
		delete[] E[0];
		delete[] E;
		E = nullptr;

		return vBack;
	}
	else
		return NULL;
}

template <typename Tv, typename Te>
bool graph<Tv, Te>::is_edge_exists(int i, int j)
{
	return i >= 0 && i < ver_num && j >= 0 && j < ver_num && E[i][j];
}

template <typename Tv, typename Te>
Te graph<Tv, Te>::get_edge_data(int i, int j)
{
	if (i >= 0 && i < ver_num && j >= 0 && j < ver_num && E[i][j])
		return E[i][j]->data;
	else
		return NULL;
}

template <typename Tv, typename Te>
int graph<Tv, Te>::get_edge_weight(int i, int j)
{
	if (i >= 0 && i < ver_num && j >= 0 && j < ver_num && E[i][j])
		return E[i][j]->weight;
	else
		return -1;
}

template <typename Tv, typename Te>
Te graph<Tv, Te>::update_edge_data(int i, int j, Te _data)
{
	if (i >= 0 && i < ver_num && j >= 0 && j < ver_num && E[i][j])
	{
		Te _return = E[i][j]->data;
		E[i][j]->data = _data;
		return _return;
	}
	else
		return NULL;
}

template <typename Tv, typename Te>
int graph<Tv, Te>::update_edge_weight(int i, int j, int _weight)
{
	if (i >= 0 && i < ver_num && j >= 0 && j < ver_num && E[i][j])
	{
		int _return = E[i][j]->weight;
		E[i][j]->weight = _weight;
		return _return;
	}
	else
		return -1;
}

template <typename Tv, typename Te>
void graph<Tv, Te>::insert_edge(Te _data, int _weight, int i, int j)
{
	if (i >= 0 && i < ver_num && j >= 0 && j < ver_num && E[i][j])
		std::cout << "该边已存在,无法插入边" << std::endl;
	else if (i >= 0 && i < ver_num && j >= 0 && j < ver_num)
	{
		E[i][j] = new edge<Te>(_data, _weight);
		V[i]->out_degree++;
		V[j]->in_degree++;
		edge_num++;
	}
	else
		std::cout << "索引越界,无法插入边" << std::endl;
}

template <typename Tv, typename Te>
Te graph<Tv, Te>::remove_edge(int i, int j)
{
	if (i >= 0 && i < ver_num && j >= 0 && j < ver_num && E[i][j])
	{
		Te eBack = E[i][j]->data;
		delete E[i][j];
		E[i][j] = nullptr;
		V[i]->out_degree--;
		V[j]->in_degree--;
		edge_num--;

		return eBack;
	}
	else
	{
		std::cout << "无法删除边" << std::endl;
		return NULL;
	}
}

template <typename Tv, typename Te>
void graph<Tv, Te>::print()
{
	if (ver_num > 0)
	{
		std::cout << "总共有" << ver_num << "个结点" << std::endl;
		for (int i = 0; i < ver_num; i++)
			std::cout << i << "号结点,信息:" << V[i]->data << " 入度:" << V[i]->in_degree << " 出度:" << V[i]->out_degree << std::endl;

		if (edge_num > 0)
		{
			std::cout << std::endl << "总共有" << edge_num << "条边" << std::endl;
			for (int i = 0; i < ver_num; i++)
				for (int j = 0; j < ver_num; j++)
					if (E[i][j])
						std::cout << "从" << i << "号结点到" << j << "号结点有一条边,信息:" << E[i][j]->data << " 权重:" << E[i][j]->weight << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << std::endl << "该图没有边" << std::endl << std::endl;
		}
	}
	else
		std::cout << "该图尚未初始化" << std::endl << std::endl;
}

} // hjr end