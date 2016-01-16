# Graphs - path search problems implemented in python

class Graph(object):
  def __init__(self, graph):
    self.graph = graph

  def get_src_to_dest_path(self, src, dest, path=[]):
    # Don't use append() since it actually appends the reference
    path = path + [src]
    # return path if we reached destination
    if src == dest:
      return path
    # return None if src is not in graph (no path exists)
    if src not in self.graph:
      return None
    # For every node in list which is not in the traversed path,
    # see if we can reach dest
    for node in self.graph[src]:
      if node not in path:
        new_path = self.get_src_to_dest_path(node, dest, path)
        if new_path:
          return new_path
    return None

  def get_all_src_to_dest_paths(self, src, dest, path=[]):
    # Same as single path, difference is to keep track of all possible paths
    # and returns list of paths.
    path = path + [src]
    if src == dest:
      return [path]
    if src not in self.graph:
      return []
    paths = []
    for node in self.graph[src]:
      if node not in path:
        new_paths = self.get_all_src_to_dest_paths(node, dest, path)
        # Keep track of all paths from src to dest
        for path_n in new_paths:
          paths.append(path_n)
    return paths

  def get_shortest_src_to_dest_path(self, src, dest, path=[]):
    # Get all the paths and save only shortest till that time.
    path = path + [src]
    if src == dest:
      return path
    if src not in self.graph:
      return None
    short_path = None
    for node in self.graph[src]:
      if node not in path:
        new_path = self.get_shortest_src_to_dest_path(node, dest, path)
        # Keep track of all paths from src to dest
        if new_path:
          if not short_path or (len(new_path) < len(short_path)):
            short_path = new_path
    return short_path

if __name__ == "__main__":
  graph1 = { 'A': ['B', 'C'],
      'B': ['D', 'E'],
      'C': ['A'],
      'D': ['F', 'E'],
      'E': ['B'],
      'F': ['G'],
      'H': [] }
  graph = Graph(graph1)
  print graph.get_src_to_dest_path('A', 'E')
  print graph.get_all_src_to_dest_paths('A', 'E')
  print graph.get_shortest_src_to_dest_path('A', 'E')