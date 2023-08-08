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
    for line in lines:
        if '-' in line:
            edge = tuple(line.split('-'))
            edges.append(edge)
        elif '##' not in line:
            node_info = line.split()
            node = node_info[0]
            nodes.append(node)
    pos = { node_info[0]: (float(node_info[1]), float(node_info[2])) for node_info in [line.split() for line in lines if '##' not in line and '-' not in line] }

    return nodes, edges, pos

def visualize_graph(nodes, edges, pos, node_color='skyblue', font_color='black', font_weight='bold', node_size=1500):
    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)

    nx.draw(G, pos, with_labels=True, node_color=node_color, font_color=font_color, font_weight=font_weight, node_size=node_size)
    plt.show()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="visuallizer")

    parser.add_argument("-i", "--input", type=str, default=None,
                        help="Input graph's info.")

    args = parser.parse_args()

    if args.input:
        input_string = read_input_file(args.input)
        nodes, edges, pos = parse_input(input_string)
        #print("nodes:", nodes)
        #print("edges:", edges)
        #print("positions:", pos)

        visualize_graph(nodes, edges, pos)
    else:
        print(f"Usage: python {sys.argv[0]} -h")

