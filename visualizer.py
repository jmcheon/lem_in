import networkx as nx
import matplotlib.pyplot as plt
import sys, argparse

def read_input_file(file_path):
    with open(file_path, 'r') as file:
        input_string = file.read()
    return input_string

def parse_input(input_string):
    lines = input_string.strip().split('\n')
    nodes = []
    edges = []
    start_flag = 0
    end_flag = 0
    start_node = 0
    end_node = 0

    for line in lines:
        if '-' in line:
            edge = tuple(line.split('-'))
            edges.append(edge)
        elif line == '##start':
            start_flag = 1
        elif line == '##end':
            end_flag = 1
        elif '##' not in line and len(line) > 1:
            node_info = line.split()
            node = node_info[0]
            nodes.append(node)
            if start_flag == 1:
                start_node = node_info[0]
                start_flag = 0
            if end_flag == 1:
                end_node = node_info[0]
                end_flag = 0
    pos = { node_info[0]: (float(node_info[1]), float(node_info[2])) for node_info in [line.split() for line in lines if '##' not in line and len(line) > 1 and '-' not in line] }

    return nodes, edges, pos, start_node, end_node

def visualize_graph(nodes, edges, pos, node_color='skyblue', font_color='black', font_weight='bold', node_size=1500, legend=None):
    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)

    nx.draw(G, pos, with_labels=True, node_color=node_color, font_color=font_color, font_weight=font_weight, node_size=node_size)
    if legend:
        for label, color in legend.items():
            plt.scatter([], [], c=color, label=label, s=node_size)
        plt.legend(scatterpoints=1, frameon=False, labelspacing=1.5)
    plt.show()


if __name__ == "__main__":
    legend = {'Start': 'green', 'End': 'red'}



    parser = argparse.ArgumentParser(description="visuallizer")

    parser.add_argument("-i", "--input", type=str, default=None,
                        help="Input graph's info.")

    args = parser.parse_args()

    if args.input:

        input_string = read_input_file(args.input)
        nodes, edges, pos, start_node, end_node = parse_input(input_string)
        #print(start_node, end_node)
        node_color = ['green' if node == start_node else 'red' if node == end_node else 'skyblue' for node in nodes]
        #print(node_color)
        #print("nodes:", nodes)
        #print("edges:", edges)
        #print("positions:", pos)

        visualize_graph(nodes, edges, pos, node_color=node_color, legend=legend)
    else:
        print(f"Usage: python {sys.argv[0]} -h")
