import networkx as nx
import matplotlib.pyplot as plt
import sys, argparse, os

def read_input_file(file_path):
    try:
        with open(file_path, 'r') as file:
            input_string = file.read()
    except:
        print("Input error: invalid file.")
        return None
    return input_string

def parse_ant_movements(ant_movements, start_node):
    ant_paths = {}

    lines = ant_movements.strip().split('\n')
    ant_count = len(lines[0].split(' '))
    print('paths num:', ant_count)
    
    for line in lines:
        movements_in_line = line.split(' ')

        for index, movement in enumerate(movements_in_line):
            ant_number = index % ant_count + 1
            _, node_info = movement.split('-')

            if ant_number not in ant_paths:
                ant_paths[ant_number] = [node_info]
            else:
                ant_paths[ant_number].append(node_info)
                
    print('ant_paths:', ant_paths)
    return ant_paths

def parse_ant_movements2(ant_movements_string, start_node):
    ant_paths = []

    lines = []
    for line in ant_movements_string.strip().split('\n'):
        lines.append(line.split(' '))
    #print(lines)

    parsed_list = [[tuple(s.split('-')) for s in line] for line in lines]
    #print(parsed_list)


    for line in parsed_list:
        #print('line:', line)
        for elem in line:
            #print('elem:', elem)
            ant_info, node_info = elem 
            ant_number = int(ant_info[1:])
            node_name = node_info
            #print('ant num:', ant_number, 'node name:', node_name)
            #print(f"L{ant_number}-{node_name}")

            if len(ant_paths) < ant_number:
                ant_paths.append([start_node])
            ant_paths[ant_number - 1].append(node_name)

    print('ant_paths:', ant_paths)
    return ant_paths


def parse_input(input_string):
    lines = input_string.strip().split('\n')
    nodes = []
    edges = []
    pos = {}

    start_flag = 0
    end_flag = 0
    start_node = 0
    end_node = 0

    for line in lines:
        if '-' in line and '#' not in line:
            edge = tuple(line.split('-'))
            edges.append(edge)
        elif line == '##start':
            start_flag = 1
        elif line == '##end':
            end_flag = 1
        elif ('##' and '#') not in line and line is not lines[0]:
            #print('line:', line)
            node_info = line.split()
            node = node_info[0]
            nodes.append(node)
            if start_flag == 1:
                start_node = node_info[0]
                start_flag = 0
            if end_flag == 1:
                end_node = node_info[0]
                end_flag = 0
            pos[node] = (float(node_info[1]), float(node_info[2]))

    return nodes, edges, pos, start_node, end_node

def visualize_graph(input_string, node_color='skyblue', font_color='black', font_weight='bold', node_size=1500, legend=None):

    nodes, edges, pos, start_node, end_node = parse_input(input_string)
    node_colors = ['green' if node == start_node else 'red' if node == end_node else 'skyblue' for node in nodes]

    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)

    nx.draw(G, pos, with_labels=True, node_color=node_colors, font_color=font_color, font_weight=font_weight, node_size=node_size)
    if legend:
        for label, color in legend.items():
            plt.scatter([], [], c=color, label=label, s=node_size)
        plt.legend(scatterpoints=1, frameon=False, labelspacing=1.5)
    plt.show()

def visualize_ants(input_string, ant_movements_string, node_colors=None,
                  font_color='black', font_weight='bold', node_size=1500):

    nodes, edges, pos, start_node, end_node = parse_input(input_string)
    ant_paths = parse_ant_movements(ant_movements_string, start_node)
    node_colors = ['green' if node == start_node else 'red' if node == end_node else 'skyblue' for node in nodes]

    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)

    nx.draw(G, pos, with_labels=True, node_color=node_colors,
            font_color=font_color, font_weight=font_weight, node_size=node_size)

    # Plot ant paths
    for i, path in enumerate(ant_paths):
        edge_list = [(path[i], path[i + 1]) for i in range(len(path) - 1)]
        edge_colors = [plt.get_cmap('Oranges')(i / len(ant_paths)) for j in range(len(edge_list))]
        nx.draw_networkx_edges(G, pos, edgelist=edge_list, edge_color=edge_colors, width=2)

    plt.show()

def load_ant_movements_string(file_path):
    file_name = os.path.basename(file_path)
    graph_name, _ = os.path.splitext(file_name)
    ant_movements_path = f"paths/{graph_name}.path"
    ant_movements_string = read_input_file(ant_movements_path)

    return ant_movements_string

if __name__ == "__main__":
    legend = {'Start': 'green', 'End': 'red'}

    parser = argparse.ArgumentParser(description="visuallizer")

    parser.add_argument("-i", "--input", type=str, default=None,
                        help="Input graph's info.")

    args = parser.parse_args()

    if args.input:

        input_string = read_input_file(args.input)

        ant_movements_string = load_ant_movements_string(args.input)
        print(ant_movements_string)

        if input_string:
            visualize_graph(input_string, legend=legend)
        if ant_movements_string:
            visualize_ants(input_string, ant_movements_string)
    else:
        print(f"Usage: python {sys.argv[0]} -h")


