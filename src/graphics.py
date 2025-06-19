import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os


trees = ['bst', 'avl', 'rbt']
directory = 'docs/'

data = {}
n_docs = {}
n_words = {}
total_insertion_time = {}
avg_insertion_time = {}
total_search_time = {}
avg_search_time = {}
max_search_time = {}
min_search_time = {}
total_comparisons = {}
avg_comparisons = {}
biggest_branch = {}
smallest_branch = {}

for tree in trees:
    data[tree] = pd.read_csv(f"docs/benchmark_results_{tree}.csv")
    n_docs[tree] = data[tree][:, 0]
    n_words[tree] = data[tree][:, 1]
    total_insertion_time[tree] = data[tree][:, 2]
    avg_insertion_time[tree] = data[tree][:, 3]
    total_search_time[tree] = data[tree][:, 5]
    avg_search_time[tree] = data[tree][:, 6]
    max_search_time[tree] = data[tree][:, 7]
    min_search_time[tree] = data[tree][:, 8]
    total_comparisons[tree] = data[tree][:, 9]
    avg_comparisons[tree] = data[tree][:, 10]
    biggest_branch[tree] = data[tree][:, 11]
    smallest_branch[tree] = data[tree][:, 12]

# número de comparações
for tree in trees:
    plt.plot(n_words[tree], total_comparisons[tree], '-', label=f"Total {tree.capitalize}")
    plt.plot(n_words[tree], avg_comparisons[tree], '--', label=f"Média {tree.capitalize}")

plt.figure()
plt.legend()
plt.xlabel("Número de arquivos")
plt.ylabel("Número de comparações")
plt.title("Número de comparações em cada árvore")
plt.show()

filepath = os.path.join(directory, "comparisons.png")
plt.savefig(filepath)


# galhos
for tree in trees:
    plt.plot(n_words[tree], biggest_branch[tree], '-', label=f"Maior {tree.capitalize}")
    plt.plot(n_words[tree], smallest_branch[tree], '--', label=f"Menor {tree.capitalize}")

plt.figure()
plt.legend()
plt.xlabel("Número de arquivos")
plt.ylabel("Tamanho do caminho")
plt.title("Maior e menor caminhos em cada árvore")
plt.show()

filepath = os.path.join(directory, "paths.png")
plt.savefig(filepath)

# tempo de busca
for tree in trees:
    plt.plot(n_words[tree], min_search_time[tree], '-', label=f"Mínimo {tree.capitalize}")
    plt.plot(n_words[tree], avg_search_time[tree], '--', label=f"Média {tree.capitalize}")
    plt.plot(n_words[tree], max_search_time[tree], ':', label=f"Máximo {tree.capitalize}")

plt.figure()
plt.legend()
plt.xlabel("Número de arquivos")
plt.ylabel("Tempo de busca")
plt.title("Tempos de busca em cada árvore")
plt.show()


filepath = os.path.join(directory, "search_time.png")
plt.savefig(filepath)

# tempo de inserção
for tree in trees:
    plt.plot(n_words[tree], total_insertion_time[tree], '-', label=f"Total {tree.capitalize}")
    plt.plot(n_words[tree], avg_insertion_time[tree], '--', label=f"Média {tree.capitalize}")

plt.figure()
plt.legend()
plt.xlabel("Número de arquivos")
plt.ylabel("Tempo de inserção")
plt.title("Tempos de inserção em cada árvore")
plt.show()


filepath = os.path.join(directory, "insertion_time.png")
plt.savefig(filepath)

