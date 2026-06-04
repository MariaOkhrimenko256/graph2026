#include <string>
#include <nlohmann/json.hpp>
#include <graph.hpp>
#include <weighted_graph.hpp>
#include <stor_vagner.hpp>

using graph::WeightedGraph;

namespace graph {

template<typename GraphType>
int StorVagnerMethodHelper(const nlohmann::json& input,
    nlohmann::json* output);

int StorVagnerMethod(const nlohmann::json& input,
    nlohmann::json* output) {
  std::string graphType = input.at("graph_type");

  if (graphType == "WeightedGraph") {
    std::string weightType = input.at("weight_type");
    if (weightType == "int") {
      return StorVagnerMethodHelper<WeightedGraph<int>>(input, output);
    } else if (weightType == "double") {
      return StorVagnerMethodHelper<WeightedGraph<double>>(
          input, output);
    } else {
      return -1;
    }
  }

  return -1;
}

template<typename GraphType>
int StorVagnerMethodHelper(const nlohmann::json& input,
    nlohmann::json* output) {
  GraphType graph;

  for (auto& vertex : input.at("vertices")) {
    graph.AddVertex(vertex);
  }

  for (auto& edge : input.at("edges")) {
    graph.AddEdge(edge.at("from"), edge.at("to"), edge.at("weight"));
  }

  (*output)["result"] = StorVagner(graph);

  return 0;
}

}  // namespace graph
