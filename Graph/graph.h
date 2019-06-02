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
#pragma once
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>

namespace hjr {

template <typename Tv>
struct vertex
{
	Tv data;
	int in_degree;
	int out_degree;
	vertex(Tv x)
	{
		data = x;
		in_degree = 0;
		out_degree = 0;
	}
};

template <typename Te>
struct edge
{
	Te data;
	int weight;
	edge(Te x, int _wei)
	{
		data = x;
		weight = _wei;
	}
};

template <typename Tv, typename Te>
class graph
{
private:
	int ver_num;
	int edge_num;
	vertex<Tv>** V;
	edge<Te>*** E;
public:
	graph();
	graph(bool isInit);
	graph(const graph& ano);
	~graph();
	Tv get_ver_data(int i);
	int get_ver_indegree(int i);
	int get_ver_outdegree(int i);
	int insert_ver(Tv _data);
	Tv remove_ver(int i);
	bool is_edge_exists(int i, int j);
	Te get_edge_data(int i, int j);
	int get_edge_weight(int i, int j);
	void insert_edge(Te _data, int _weight, int i, int j);
	Te remove_edge(int i, int j);
	void print();
};

} // hjr end

#endif // !GRAPH_H

