import matplotlib.pyplot as mplt
import matplotlib.patches as mpatches
import numpy as np
from mpl_toolkits import mplot3d

def PcaIris2D(X_r, y, target_names, title = 'PCA of IRIS dataset'):
    mplt.figure()
    colors = ['navy', 'turquoise', 'darkorange']
    lw = 2

    for color, i, target_name in zip(colors, [0, 1, 2], target_names):
        mplt.scatter(X_r[y == i, 0], X_r[y == i, 1], color=color, alpha=.8, lw=lw,
                    label=target_name)
    mplt.legend(loc='best', shadow=False, scatterpoints=1)
    mplt.title(title)
    mplt.show()

def LdaIris2D(X_lda, y, label_dict, title = 'Plot Lda'):
    ax = mplt.subplot(111)
    for label,marker,color in zip(
        range(0,3),('^', 's', 'o'),('blue', 'red', 'green')):
            mplt.scatter(x=X_lda[:,0].real[y == label],
                y=X_lda[:,1].real[y == label],
                marker=marker,
                color=color,
                alpha=0.5,
                label=label_dict[label]
            )

    mplt.xlabel('LD1')
    mplt.ylabel('LD2')

    leg = mplt.legend(loc='upper right', fancybox=True)
    leg.get_frame().set_alpha(0.5)
    mplt.title(title)

    # hide axis ticks
    mplt.tick_params(axis="both", which="both", bottom="off", top="off",  
            labelbottom="on", left="off", right="off", labelleft="on")

    # remove axis spines
    ax.spines["top"].set_visible(False)  
    ax.spines["right"].set_visible(False)
    ax.spines["bottom"].set_visible(False)
    ax.spines["left"].set_visible(False)    

    mplt.grid()
    mplt.tight_layout
    mplt.show()