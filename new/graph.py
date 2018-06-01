#!/usr/bin/python3

import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

import argparse


def surface(data, file):
    Z = np.array(data)
    X = np.arange(0, 1, 1.0 / Z.shape[1])
    Y = np.arange(0, 1, 1.0 / Z.shape[1])
    X2D, Y2D = np.meshgrid(X, Y)
    fig = plt.figure()
    ax = Axes3D(fig)
    ax.plot_surface(X2D, Y2D, Z)
    plt.subplots_adjust(wspace=0.5, hspace=0.6)
    plt.savefig('{}.png'.format(file))


def build_efficiency_plots(mean_values, file):
    fig = plt.figure(figsize=(8, 6), dpi=100)
    rt_subplt = fig.add_subplot(211) #212
    Sp_subplt = fig.add_subplot(223) #221
    Ep_subplt = fig.add_subplot(224) #222

    rt_subplt.set_title('Время выполнения, сек')
    rt_subplt.set_xlabel('Число потоков')
    rt_subplt.set_ylabel('Время')
    Sp_subplt.set_title('Ускорение')
    Sp_subplt.set_xlabel('Число потоков')
    Sp_subplt.set_ylabel("$S_{p}$")
    Ep_subplt.set_title('Эффективность')
    Ep_subplt.set_xlabel('Число потоков')
    Ep_subplt.set_ylabel("$E_{p}$")

    for dimension in sorted(set(mean_values['Dimension'])):
        sub_df = mean_values.loc[mean_values.Dimension == dimension]
        one_thread_t = sub_df[sub_df.NumThreads == 1]['Runtime'].astype(float)
        speedup = np.array(one_thread_t) / np.array(sub_df['Runtime'])
        efficiency = speedup / np.array(sub_df['NumThreads'])

        rt_subplt.plot(sub_df['NumThreads'], sub_df['Runtime'],
                       marker="o", label="{dim}x{dim}".format(dim=dimension))
        Sp_subplt.plot(sub_df['NumThreads'], speedup, marker=".",
                       label="{dim}x{dim}".format(dim=dimension))
        Ep_subplt.plot(sub_df['NumThreads'], efficiency,
                       marker=".", label="{dim}x{dim}".format(dim=dimension))
    rt_subplt.legend(bbox_to_anchor=(1, 1))
    plt.subplots_adjust(wspace=0.5, hspace=0.6)
    plt.savefig('{}.png'.format(file))


if __name__ == '__main__':
    max_threads = 4
    step = 1
    dim = [100, 500, 1000, 2000]
    b_data = pd.DataFrame(columns = ["NumThreads", "Iterations", "Runtime", "Dimension", "EPS"])
    first = True
    for d in dim:
        first = True
        for x in range(1, max_threads+1, step):
            file = open("res/result_{}_{}.txt".format(x,d))
            a = file.readline().strip().split(',')
            a = list(map(float,a))
            b_data.loc[len(b_data)] = a
            lines = file.readlines()
            matrix = []; app = []; app2 = []
            for line in lines:
                line = line.strip().split(' ')
                app.append(line)
            for row in app:
                for item in row:
                    #print(item)
                    if item!='':
                        matrix.append(float(item))
            #print(lines)
            matrix = np.array(matrix)
            matrix = np.reshape(matrix, (d, d))
            #print(matrix.shape[0][1])
            if first:
                surface(matrix, "plots/surface_{}_{}".format(x,d))
                first = False
    data = b_data.groupby(['NumThreads', 'Dimension'], as_index=False).mean()
    build_efficiency_plots(data, "plots/plot")
