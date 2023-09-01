import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import sys, argparse, os
import random

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
    
    for line in lines:
        if line.startswith("L") and "-" in line:
            movements_in_line = line.split()
            #print('test: ', movements_in_line)

            for index, movement in enumerate(movements_in_line):
                ant_number, node_info = movement.split('-')
                ant_index = int(ant_number[1:])

                if ant_index not in ant_paths:
                    ant_paths[ant_index] = [start_node]
                ant_paths[ant_index].append(node_info)
                
    #print('ant_paths:', ant_paths)
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
        if not (line.startswith("L") and "-" in line) and not line == '':
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

def visualize_graph(input_string, font_color='black', font_weight='bold', node_size=1500, legend=None):

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

def visualize_ants(input_string, font_color='black', font_weight='bold', node_size=1500):

    nodes, edges, pos, start_node, end_node = parse_input(input_string)
    ant_paths = parse_ant_movements(input_string, start_node)
    #print('ant_paths:', ant_paths)
    node_colors = ['green' if node == start_node else 'red' if node == end_node else 'skyblue' for node in nodes]

    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)

    nx.draw(G, pos, with_labels=True, node_color=node_colors,
            font_color=font_color, font_weight=font_weight, node_size=node_size)

    # Plot ant paths
    for ant, path in ant_paths.items():
        #print('path:', path)
        edge_list = [(path[i], path[i + 1]) for i in range(len(path) - 1)]
        edge_colors = [plt.get_cmap('Oranges')(ant / len(ant_paths)) for j in range(len(edge_list))]
        nx.draw_networkx_edges(G, pos, edgelist=edge_list, edge_color=edge_colors, width=2)

    plt.show()

def generate_random_color():
    # Generate a random color in hex format
    color = "#{:02x}{:02x}{:02x}".format(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
    return color

def animate_ants(input_string, print_flag=False, interval=1000):
    nodes, edges, pos, start_node, end_node = parse_input(input_string)

    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)

    if print_flag:
        fig, (ax, ax2) = plt.subplots(1, 2, figsize=(12, 6))
        ax2.axis("off")
        text_display = ax2.text(0.5, 0.5, '', transform=ax2.transAxes, ha='center', fontsize=12)
    else:
        fig, ax = plt.subplots(figsize=(8, 6))

    node_colors = ['green' if node == start_node else 'red' if node == end_node else 'skyblue' for node in nodes]
    nx.draw(G, pos, with_labels=True, node_color=node_colors, ax=ax)

    lines = input_string.strip().split('\n')
    ant_frames = []#input_string.strip().split('\n')

    for line in lines:
        if line.startswith("L") and "-" in line:
            ant_frames.append(line)

    ant_colors = {}

    def animate(frame):
        ax.clear()
        nx.draw(G, pos, with_labels=True, node_color=node_colors, ax=ax)
        
        if frame < len(ant_frames):
            ant_path = ant_frames[frame].split()
            for ant_node in ant_path:
                ant_id, node = ant_node.split('-')
                if ant_id not in ant_colors:
                    ant_colors[ant_id] = generate_random_color()
                color = ant_colors[ant_id]
                nx.draw_networkx_nodes(G, pos, nodelist=[node], node_color=color, ax=ax)
            if print_flag:
                text_display.set_text("Frame: {}\n{}".format(frame, ant_path))

    ani = FuncAnimation(fig, animate, frames=len(ant_frames),
                        interval=interval, repeat=False)

    plt.show()

def load_ant_movements_string(file_path):
    file_name = os.path.basename(file_path)
    graph_name, _ = os.path.splitext(file_name)
    ant_movements_path = f"paths/{graph_name}.path"
    ant_movements_string = read_input_file(ant_movements_path)

    return ant_movements_string

if __name__ == "__main__":
    legend = {'Start': 'green', 'End': 'red'}

    parser = argparse.ArgumentParser(description="This is a visuallizer for 42 project lem-in.")

    parser.add_argument("-g", "--graph", action="store_true", default=False,
                        help="Plot the graph")

    parser.add_argument("-p", "--paths", action="store_true", default=False,
                        help="Plot the paths")

    parser.add_argument("-a", "--ants", action="store_true", default=False,
                        help="Plot the ants movements")

    args = parser.parse_args()

    input_string = sys.stdin.read() 

    if input_string:

        #input_string = read_input_file(args.input)

        #ant_movements_string = load_ant_movements_string(input_string)
        #print(ant_movements_string)

        if input_string and args.graph:
            visualize_graph(input_string)
        if input_string and args.paths:
            visualize_ants(input_string)
        if input_string and args.ants:
            animate_ants(input_string)
    else:
        print(f"Usage: python {sys.argv[0]} -h")


