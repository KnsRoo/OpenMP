import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import math


def buildPlot(name_plots, data, max_y_time, max_y_sp=4, max_y_ep=2):
    fig = plt.figure(figsize=(8, 6), dpi=100)
    rt_subplt = fig.add_subplot(211)
    plt.ylim(0, max_y_time)
    plt.grid(ls=':')
    Sp_subplt = fig.add_subplot(223)
    plt.ylim(0, max_y_sp)
    plt.grid(ls=':')
    Ep_subplt = fig.add_subplot(224)
    plt.ylim(0, max_y_ep)
    plt.grid(ls=':')

    rt_subplt.set_title('Время выполнения, сек')
    rt_subplt.set_xlabel('число потоков')
    rt_subplt.set_ylabel('time')
    Sp_subplt.set_title('Ускорение')
    Sp_subplt.set_xlabel('число потоков')
    Sp_subplt.set_ylabel("$S_{p}$")
    Ep_subplt.set_title('Эффективность')
    Ep_subplt.set_xlabel('число потоков')
    Ep_subplt.set_ylabel("$E_{p}$")

    for dimension in sorted(set(data['Dimension'])):
        sub_df = data.loc[data.Dimension == dimension]
        one_thread_t = float(sub_df[sub_df.Threads == 1]['RunTime'])
        speedup = one_thread_t / np.array(sub_df['RunTime'])
        efficiency = speedup / np.array(sub_df['Threads'])

        rt_subplt.plot(sub_df['Threads'], sub_df['RunTime'], marker=".", label="{dim}x{dim}".format(dim=dimension))
        Sp_subplt.plot(sub_df['Threads'], speedup, marker=".", label="{dim}x{dim}".format(dim=dimension))
        Ep_subplt.plot(sub_df['Threads'], efficiency, marker=".", label="{dim}x{dim}".format(dim=dimension))
    rt_subplt.legend()

    fig.subplots_adjust(wspace=0.5, hspace=0.5)
    fig.savefig(name_plots + '.png')


if __name__ == "__main__":
    data_1 = pd.read_csv('result_1.csv').groupby(['Threads', 'Dimension'], as_index=False).mean()
    data_2 = pd.read_csv('result_2.csv').groupby(['Threads', 'Dimension'], as_index=False).mean()
    max_time = max(max(data_1['RunTime']), max(data_2['RunTime']))

    buildPlot('mult_1', data_1, max_time, 20)
    buildPlot('mult_2', data_2, max_time, 20)
