import argparse
import numpy as np
import uproot
import awkward as ak
import matplotlib.pyplot as plt

class ROOT():
    def __init__(self, root_file):
        self.root_file = root_file
        self.fnl = {}   #final features and labels

    def read_root_data(self):
        self.hep_tree = hep_tree = uproot.open(self.root_file)["tree"]
        first_10_branches = list(hep_tree.keys())[:10]
        self.hep_tree.show(filter_name=first_10_branches, name_width=50, typename_width=50, interpretation_width=50)

    def clip(self, a, a_min, a_max):
        try:
            return np.clip(a, a_min, a_max)
        except ValueError:
            return ak.unflatten(np.clip(ak.flatten(a), a_min, a_max), ak.num(a))

    def pad(self, a, maxlen, value=0, dtype='float32'):
        if isinstance(a, np.ndarray) and a.ndim >= 2 and a.shape[1] == maxlen:
            return a
        elif isinstance(a, ak.Array):
            if a.ndim == 1:
                a = ak.unflatten(a, 1)
            a = ak.fill_none(ak.pad_none(a, maxlen, clip=True), value)
            return ak.values_astype(a, dtype)
        else:
            x = (np.ones((len(a), maxlen)) * value).astype(dtype)
            for idx, s in enumerate(a):
                if not len(s):
                    continue
                trunc = s[:maxlen].astype(dtype)
                x[idx, :len(trunc)] = trunc
            return x

    def get_features_and_labels(self, normalize_features=True, feature=None):
        # load arrays from the tree (arrays may be of different lengths so will require padding or clipping)
        a = self.hep_tree.arrays(filter_name=['part_*', 'jet_pt', 'jet_energy', 'label_*'])
        if feature is None:
            # compute new features
            a['part_mask'] = ak.ones_like(a['part_energy'])
            a['part_pt'] = np.hypot(a['part_px'], a['part_py'])
            a['part_pt_log'] = np.log(a['part_pt'])
            a['part_e_log'] = np.log(a['part_energy'])
            a['part_logptrel'] = np.log(a['part_pt']/a['jet_pt'])
            a['part_logerel'] = np.log(a['part_energy']/a['jet_energy'])
            a['part_deltaR'] = np.hypot(a['part_deta'], a['part_dphi'])
            a['part_d0'] = np.tanh(a['part_d0val'])
            a['part_dz'] = np.tanh(a['part_dzval'])

            # apply standardization
            if normalize_features:
                a['part_pt_log'] = (a['part_pt_log'] - 1.7) * 0.7
                a['part_e_log'] = (a['part_e_log'] - 2.0) * 0.7
                a['part_logptrel'] = (a['part_logptrel'] - (-4.7)) * 0.7
                a['part_logerel'] = (a['part_logerel'] - (-4.7)) * 0.7
                a['part_deltaR'] = (a['part_deltaR'] - 0.2) * 4.0
                a['part_d0err'] = self.clip(a['part_d0err'], 0, 1)
                a['part_dzerr'] = self.clip(a['part_dzerr'], 0, 1)

            feature_list = {
                'pf_points': ['part_deta', 'part_dphi'], # not used in ParT
                'pf_features': ['part_pt_log', 'part_e_log','part_logptrel','part_logerel','part_deltaR','part_charge','part_isChargedHadron','part_isNeutralHadron','part_isPhoton','part_isElectron','part_isMuon','part_d0','part_d0err','part_dz','part_dzerr','part_deta','part_dphi'],
                'pf_vectors': ['part_px','part_py','part_pz','part_energy'],
                'pf_mask': ['part_mask']
            }

            for k, names in feature_list.items():
                self.fnl[k] = np.stack([self.pad(a[n], maxlen=126).to_numpy() for n in names], axis=1)

            label_list = ['label_QCD', 'label_Hbb', 'label_Hcc', 'label_Hgg', 'label_H4q', 'label_Hqql', 'label_Zqq', 'label_Wqq', 'label_Tbqq', 'label_Tbl']
            self.fnl['label'] = np.stack([a[n].to_numpy().astype('int') for n in label_list], axis=1)

        else:
            self.fnl[feature] = self.pad(a[feature], maxlen=126).to_numpy()

    def plot_histpgram(self, feature, n_bins=100):
        plt.hist(self.fnl[feature], bins=n_bins)
        plt.title(f'${feature}$ distribution')
        plt.xlabel(f'${feature}$')
        plt.ylabel('Number of particles')
        plt.show()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--root", required=True, help="path to .root HEP data file")
    args = parser.parse_args()

    root = ROOT(args.root)
    root.read_root_data()
    root.get_features_and_labels(feature="part_px")
    root.plot_histpgram(feature="part_px")
