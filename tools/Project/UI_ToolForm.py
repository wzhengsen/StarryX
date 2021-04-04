# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'UI/ToolForm.ui'
#
# Created by: PyQt5 UI code generator 5.15.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_ToolForm(object):
    def setupUi(self, ToolForm):
        ToolForm.setObjectName("ToolForm")
        ToolForm.setWindowModality(QtCore.Qt.WindowModal)
        ToolForm.resize(600, 400)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(ToolForm.sizePolicy().hasHeightForWidth())
        ToolForm.setSizePolicy(sizePolicy)
        ToolForm.setMinimumSize(QtCore.QSize(600, 400))
        ToolForm.setMaximumSize(QtCore.QSize(600, 400))
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/res/IcoMain.ico"), QtGui.QIcon.Normal, QtGui.QIcon.On)
        ToolForm.setWindowIcon(icon)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(ToolForm)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setSpacing(2)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.TabWidget = QtWidgets.QTabWidget(ToolForm)
        self.TabWidget.setObjectName("TabWidget")
        self.TabHotUpdate = QtWidgets.QWidget()
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.TabHotUpdate.sizePolicy().hasHeightForWidth())
        self.TabHotUpdate.setSizePolicy(sizePolicy)
        self.TabHotUpdate.setObjectName("TabHotUpdate")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.TabHotUpdate)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setSpacing(2)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setSpacing(2)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.ModuleTreeWidget = QtWidgets.QTreeWidget(self.TabHotUpdate)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.ModuleTreeWidget.sizePolicy().hasHeightForWidth())
        self.ModuleTreeWidget.setSizePolicy(sizePolicy)
        self.ModuleTreeWidget.setMinimumSize(QtCore.QSize(263, 306))
        self.ModuleTreeWidget.setMaximumSize(QtCore.QSize(263, 306))
        self.ModuleTreeWidget.setSelectionBehavior(QtWidgets.QAbstractItemView.SelectItems)
        self.ModuleTreeWidget.setObjectName("ModuleTreeWidget")
        self.ModuleTreeWidget.headerItem().setText(0, "1")
        self.ModuleTreeWidget.header().setVisible(False)
        self.horizontalLayout.addWidget(self.ModuleTreeWidget, 0, QtCore.Qt.AlignLeft)
        self.SettingWidget = QtWidgets.QWidget(self.TabHotUpdate)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.SettingWidget.sizePolicy().hasHeightForWidth())
        self.SettingWidget.setSizePolicy(sizePolicy)
        self.SettingWidget.setMinimumSize(QtCore.QSize(329, 306))
        self.SettingWidget.setMaximumSize(QtCore.QSize(329, 306))
        self.SettingWidget.setObjectName("SettingWidget")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.SettingWidget)
        self.gridLayout_3.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_3.setSpacing(2)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.UploadGroupBox = QtWidgets.QGroupBox(self.SettingWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.UploadGroupBox.sizePolicy().hasHeightForWidth())
        self.UploadGroupBox.setSizePolicy(sizePolicy)
        self.UploadGroupBox.setMinimumSize(QtCore.QSize(160, 129))
        self.UploadGroupBox.setMaximumSize(QtCore.QSize(160, 129))
        self.UploadGroupBox.setObjectName("UploadGroupBox")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.UploadGroupBox)
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_2.setSpacing(2)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.NoUploadCheckBox = QtWidgets.QCheckBox(self.UploadGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.NoUploadCheckBox.sizePolicy().hasHeightForWidth())
        self.NoUploadCheckBox.setSizePolicy(sizePolicy)
        self.NoUploadCheckBox.setObjectName("NoUploadCheckBox")
        self.gridLayout_2.addWidget(self.NoUploadCheckBox, 0, 0, 1, 1)
        self.UploadDiffHashCheckBox = QtWidgets.QCheckBox(self.UploadGroupBox)
        self.UploadDiffHashCheckBox.setEnabled(True)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.UploadDiffHashCheckBox.sizePolicy().hasHeightForWidth())
        self.UploadDiffHashCheckBox.setSizePolicy(sizePolicy)
        self.UploadDiffHashCheckBox.setChecked(True)
        self.UploadDiffHashCheckBox.setObjectName("UploadDiffHashCheckBox")
        self.gridLayout_2.addWidget(self.UploadDiffHashCheckBox, 1, 0, 1, 1)
        self.UploadZipCheckBox = QtWidgets.QCheckBox(self.UploadGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.UploadZipCheckBox.sizePolicy().hasHeightForWidth())
        self.UploadZipCheckBox.setSizePolicy(sizePolicy)
        self.UploadZipCheckBox.setObjectName("UploadZipCheckBox")
        self.gridLayout_2.addWidget(self.UploadZipCheckBox, 2, 0, 1, 1)
        self.FtpAccountLineEdit = QtWidgets.QLineEdit(self.UploadGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.FtpAccountLineEdit.sizePolicy().hasHeightForWidth())
        self.FtpAccountLineEdit.setSizePolicy(sizePolicy)
        self.FtpAccountLineEdit.setText("")
        self.FtpAccountLineEdit.setMaxLength(32)
        self.FtpAccountLineEdit.setClearButtonEnabled(True)
        self.FtpAccountLineEdit.setObjectName("FtpAccountLineEdit")
        self.gridLayout_2.addWidget(self.FtpAccountLineEdit, 3, 0, 1, 1)
        self.FtpPasswordLineEdit = QtWidgets.QLineEdit(self.UploadGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.FtpPasswordLineEdit.sizePolicy().hasHeightForWidth())
        self.FtpPasswordLineEdit.setSizePolicy(sizePolicy)
        self.FtpPasswordLineEdit.setMaxLength(32)
        self.FtpPasswordLineEdit.setClearButtonEnabled(True)
        self.FtpPasswordLineEdit.setObjectName("FtpPasswordLineEdit")
        self.gridLayout_2.addWidget(self.FtpPasswordLineEdit, 4, 0, 1, 1)
        self.gridLayout_3.addWidget(self.UploadGroupBox, 0, 2, 1, 1)
        self.VersionGroupBox = QtWidgets.QGroupBox(self.SettingWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.VersionGroupBox.sizePolicy().hasHeightForWidth())
        self.VersionGroupBox.setSizePolicy(sizePolicy)
        self.VersionGroupBox.setMinimumSize(QtCore.QSize(167, 129))
        self.VersionGroupBox.setMaximumSize(QtCore.QSize(167, 129))
        self.VersionGroupBox.setObjectName("VersionGroupBox")
        self.gridLayout = QtWidgets.QGridLayout(self.VersionGroupBox)
        self.gridLayout.setContentsMargins(0, 0, 0, 0)
        self.gridLayout.setSpacing(2)
        self.gridLayout.setObjectName("gridLayout")
        self.V1RadioButton = QtWidgets.QRadioButton(self.VersionGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.V1RadioButton.sizePolicy().hasHeightForWidth())
        self.V1RadioButton.setSizePolicy(sizePolicy)
        self.V1RadioButton.setChecked(True)
        self.V1RadioButton.setObjectName("V1RadioButton")
        self.gridLayout.addWidget(self.V1RadioButton, 0, 0, 1, 2)
        self.V3RadioButton = QtWidgets.QRadioButton(self.VersionGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.V3RadioButton.sizePolicy().hasHeightForWidth())
        self.V3RadioButton.setSizePolicy(sizePolicy)
        self.V3RadioButton.setObjectName("V3RadioButton")
        self.gridLayout.addWidget(self.V3RadioButton, 2, 0, 1, 3)
        self.V4RadioButton = QtWidgets.QRadioButton(self.VersionGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.V4RadioButton.sizePolicy().hasHeightForWidth())
        self.V4RadioButton.setSizePolicy(sizePolicy)
        self.V4RadioButton.setObjectName("V4RadioButton")
        self.gridLayout.addWidget(self.V4RadioButton, 3, 0, 1, 3)
        self.V1SpinBox = QtWidgets.QSpinBox(self.VersionGroupBox)
        self.V1SpinBox.setEnabled(False)
        self.V1SpinBox.setObjectName("V1SpinBox")
        self.gridLayout.addWidget(self.V1SpinBox, 4, 0, 1, 1)
        self.V2SpinBox = QtWidgets.QSpinBox(self.VersionGroupBox)
        self.V2SpinBox.setEnabled(False)
        self.V2SpinBox.setObjectName("V2SpinBox")
        self.gridLayout.addWidget(self.V2SpinBox, 4, 1, 1, 1)
        self.V3SpinBox = QtWidgets.QSpinBox(self.VersionGroupBox)
        self.V3SpinBox.setEnabled(False)
        self.V3SpinBox.setObjectName("V3SpinBox")
        self.gridLayout.addWidget(self.V3SpinBox, 4, 2, 1, 1)
        self.V4SpinBox = QtWidgets.QSpinBox(self.VersionGroupBox)
        self.V4SpinBox.setEnabled(False)
        self.V4SpinBox.setObjectName("V4SpinBox")
        self.gridLayout.addWidget(self.V4SpinBox, 4, 3, 1, 1)
        self.V2RadioButton = QtWidgets.QRadioButton(self.VersionGroupBox)
        self.V2RadioButton.setObjectName("V2RadioButton")
        self.gridLayout.addWidget(self.V2RadioButton, 1, 0, 1, 3)
        self.gridLayout_3.addWidget(self.VersionGroupBox, 0, 1, 1, 1)
        self.DownloadGroupBox = QtWidgets.QGroupBox(self.SettingWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.DownloadGroupBox.sizePolicy().hasHeightForWidth())
        self.DownloadGroupBox.setSizePolicy(sizePolicy)
        self.DownloadGroupBox.setMinimumSize(QtCore.QSize(160, 138))
        self.DownloadGroupBox.setMaximumSize(QtCore.QSize(160, 138))
        self.DownloadGroupBox.setObjectName("DownloadGroupBox")
        self.gridLayout_5 = QtWidgets.QGridLayout(self.DownloadGroupBox)
        self.gridLayout_5.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_5.setSpacing(2)
        self.gridLayout_5.setObjectName("gridLayout_5")
        self.label = QtWidgets.QLabel(self.DownloadGroupBox)
        self.label.setEnabled(True)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        self.label.setScaledContents(False)
        self.label.setIndent(-1)
        self.label.setObjectName("label")
        self.gridLayout_5.addWidget(self.label, 0, 0, 1, 2)
        self.NumFilterCheckBox = QtWidgets.QCheckBox(self.DownloadGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.NumFilterCheckBox.sizePolicy().hasHeightForWidth())
        self.NumFilterCheckBox.setSizePolicy(sizePolicy)
        self.NumFilterCheckBox.setObjectName("NumFilterCheckBox")
        self.gridLayout_5.addWidget(self.NumFilterCheckBox, 1, 0, 1, 1)
        self.NumFilterSpinBox = QtWidgets.QSpinBox(self.DownloadGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.NumFilterSpinBox.sizePolicy().hasHeightForWidth())
        self.NumFilterSpinBox.setSizePolicy(sizePolicy)
        self.NumFilterSpinBox.setMaximum(9999)
        self.NumFilterSpinBox.setObjectName("NumFilterSpinBox")
        self.gridLayout_5.addWidget(self.NumFilterSpinBox, 1, 1, 1, 1)
        self.SizeFilterCheckBox = QtWidgets.QCheckBox(self.DownloadGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.SizeFilterCheckBox.sizePolicy().hasHeightForWidth())
        self.SizeFilterCheckBox.setSizePolicy(sizePolicy)
        self.SizeFilterCheckBox.setObjectName("SizeFilterCheckBox")
        self.gridLayout_5.addWidget(self.SizeFilterCheckBox, 2, 0, 1, 1)
        self.SizeFilterSpinBox = QtWidgets.QDoubleSpinBox(self.DownloadGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.SizeFilterSpinBox.sizePolicy().hasHeightForWidth())
        self.SizeFilterSpinBox.setSizePolicy(sizePolicy)
        self.SizeFilterSpinBox.setPrefix("")
        self.SizeFilterSpinBox.setDecimals(1)
        self.SizeFilterSpinBox.setObjectName("SizeFilterSpinBox")
        self.gridLayout_5.addWidget(self.SizeFilterSpinBox, 2, 1, 1, 1)
        self.DownloadFilterComboBox = QtWidgets.QComboBox(self.DownloadGroupBox)
        self.DownloadFilterComboBox.setGeometry(QtCore.QRect(2, 40, 51, 20))
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.DownloadFilterComboBox.sizePolicy().hasHeightForWidth())
        self.DownloadFilterComboBox.setSizePolicy(sizePolicy)
        self.DownloadFilterComboBox.setObjectName("DownloadFilterComboBox")
        self.NumFilterCheckBox.raise_()
        self.NumFilterSpinBox.raise_()
        self.SizeFilterCheckBox.raise_()
        self.SizeFilterSpinBox.raise_()
        self.label.raise_()
        self.DownloadFilterComboBox.raise_()
        self.gridLayout_3.addWidget(self.DownloadGroupBox, 1, 2, 1, 1)
        self.OtherSettingGroupBox = QtWidgets.QGroupBox(self.SettingWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.OtherSettingGroupBox.sizePolicy().hasHeightForWidth())
        self.OtherSettingGroupBox.setSizePolicy(sizePolicy)
        self.OtherSettingGroupBox.setObjectName("OtherSettingGroupBox")
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout(self.OtherSettingGroupBox)
        self.horizontalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_5.setSpacing(2)
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        self.UniqueConfigCheckBox = QtWidgets.QCheckBox(self.OtherSettingGroupBox)
        self.UniqueConfigCheckBox.setChecked(True)
        self.UniqueConfigCheckBox.setObjectName("UniqueConfigCheckBox")
        self.horizontalLayout_5.addWidget(self.UniqueConfigCheckBox)
        self.SaveOnExitCheckBox = QtWidgets.QCheckBox(self.OtherSettingGroupBox)
        self.SaveOnExitCheckBox.setChecked(True)
        self.SaveOnExitCheckBox.setObjectName("SaveOnExitCheckBox")
        self.horizontalLayout_5.addWidget(self.SaveOnExitCheckBox)
        self.gridLayout_3.addWidget(self.OtherSettingGroupBox, 2, 1, 1, 2)
        self.GenerateGroupBox = QtWidgets.QGroupBox(self.SettingWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.GenerateGroupBox.sizePolicy().hasHeightForWidth())
        self.GenerateGroupBox.setSizePolicy(sizePolicy)
        self.GenerateGroupBox.setMinimumSize(QtCore.QSize(167, 138))
        self.GenerateGroupBox.setMaximumSize(QtCore.QSize(167, 138))
        self.GenerateGroupBox.setObjectName("GenerateGroupBox")
        self.gridLayout_4 = QtWidgets.QGridLayout(self.GenerateGroupBox)
        self.gridLayout_4.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_4.setHorizontalSpacing(0)
        self.gridLayout_4.setVerticalSpacing(2)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.UncomperssZipCheckBox = QtWidgets.QCheckBox(self.GenerateGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.UncomperssZipCheckBox.sizePolicy().hasHeightForWidth())
        self.UncomperssZipCheckBox.setSizePolicy(sizePolicy)
        self.UncomperssZipCheckBox.setObjectName("UncomperssZipCheckBox")
        self.gridLayout_4.addWidget(self.UncomperssZipCheckBox, 0, 0, 1, 2)
        self.CompressResCheckBox = QtWidgets.QCheckBox(self.GenerateGroupBox)
        self.CompressResCheckBox.setChecked(True)
        self.CompressResCheckBox.setObjectName("CompressResCheckBox")
        self.gridLayout_4.addWidget(self.CompressResCheckBox, 1, 0, 1, 2)
        self.CompressPasswordLineEdit = QtWidgets.QLineEdit(self.GenerateGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.CompressPasswordLineEdit.sizePolicy().hasHeightForWidth())
        self.CompressPasswordLineEdit.setSizePolicy(sizePolicy)
        self.CompressPasswordLineEdit.setMaxLength(16)
        self.CompressPasswordLineEdit.setObjectName("CompressPasswordLineEdit")
        self.gridLayout_4.addWidget(self.CompressPasswordLineEdit, 2, 0, 1, 2)
        self.CompressImgCheckBox = QtWidgets.QCheckBox(self.GenerateGroupBox)
        self.CompressImgCheckBox.setChecked(True)
        self.CompressImgCheckBox.setObjectName("CompressImgCheckBox")
        self.gridLayout_4.addWidget(self.CompressImgCheckBox, 3, 0, 1, 2)
        self.MinQualitySpinBox = QtWidgets.QSpinBox(self.GenerateGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.MinQualitySpinBox.sizePolicy().hasHeightForWidth())
        self.MinQualitySpinBox.setSizePolicy(sizePolicy)
        self.MinQualitySpinBox.setMinimumSize(QtCore.QSize(64, 20))
        self.MinQualitySpinBox.setMinimum(50)
        self.MinQualitySpinBox.setObjectName("MinQualitySpinBox")
        self.gridLayout_4.addWidget(self.MinQualitySpinBox, 4, 0, 1, 1)
        self.MaxQualitySpinBox = QtWidgets.QSpinBox(self.GenerateGroupBox)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.MaxQualitySpinBox.sizePolicy().hasHeightForWidth())
        self.MaxQualitySpinBox.setSizePolicy(sizePolicy)
        self.MaxQualitySpinBox.setMinimum(85)
        self.MaxQualitySpinBox.setObjectName("MaxQualitySpinBox")
        self.gridLayout_4.addWidget(self.MaxQualitySpinBox, 4, 1, 1, 1, QtCore.Qt.AlignLeft)
        self.CompileLuaCheckBox = QtWidgets.QCheckBox(self.GenerateGroupBox)
        self.CompileLuaCheckBox.setChecked(True)
        self.CompileLuaCheckBox.setObjectName("CompileLuaCheckBox")
        self.gridLayout_4.addWidget(self.CompileLuaCheckBox, 5, 0, 1, 2)
        self.gridLayout_3.addWidget(self.GenerateGroupBox, 1, 1, 1, 1)
        self.horizontalLayout.addWidget(self.SettingWidget, 0, QtCore.Qt.AlignRight)
        self.horizontalLayout.setStretch(0, 4)
        self.horizontalLayout.setStretch(1, 5)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_4.setSpacing(0)
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setContentsMargins(2, 2, 2, 2)
        self.horizontalLayout_2.setSpacing(2)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.SelectAllButton = QtWidgets.QPushButton(self.TabHotUpdate)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/res/ImgPlus.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.SelectAllButton.setIcon(icon1)
        self.SelectAllButton.setObjectName("SelectAllButton")
        self.horizontalLayout_2.addWidget(self.SelectAllButton)
        self.SelectOtherButton = QtWidgets.QPushButton(self.TabHotUpdate)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/res/ImgDel.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.SelectOtherButton.setIcon(icon2)
        self.SelectOtherButton.setObjectName("SelectOtherButton")
        self.horizontalLayout_2.addWidget(self.SelectOtherButton)
        spacerItem = QtWidgets.QSpacerItem(1, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem)
        self.ManageModuleButton = QtWidgets.QPushButton(self.TabHotUpdate)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.ManageModuleButton.sizePolicy().hasHeightForWidth())
        self.ManageModuleButton.setSizePolicy(sizePolicy)
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/res/ImgGear.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ManageModuleButton.setIcon(icon3)
        self.ManageModuleButton.setObjectName("ManageModuleButton")
        self.horizontalLayout_2.addWidget(self.ManageModuleButton)
        self.horizontalLayout_4.addLayout(self.horizontalLayout_2)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setContentsMargins(2, 2, 2, 2)
        self.horizontalLayout_3.setSpacing(2)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.StartTimerCheckBox = QtWidgets.QCheckBox(self.TabHotUpdate)
        self.StartTimerCheckBox.setObjectName("StartTimerCheckBox")
        self.horizontalLayout_3.addWidget(self.StartTimerCheckBox)
        self.StartTimerSpinBox = QtWidgets.QSpinBox(self.TabHotUpdate)
        self.StartTimerSpinBox.setEnabled(False)
        self.StartTimerSpinBox.setWrapping(False)
        self.StartTimerSpinBox.setAlignment(QtCore.Qt.AlignCenter)
        self.StartTimerSpinBox.setMaximum(100000)
        self.StartTimerSpinBox.setSingleStep(1800)
        self.StartTimerSpinBox.setObjectName("StartTimerSpinBox")
        self.horizontalLayout_3.addWidget(self.StartTimerSpinBox)
        spacerItem1 = QtWidgets.QSpacerItem(1, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout_3.addItem(spacerItem1)
        self.StartButton = QtWidgets.QPushButton(self.TabHotUpdate)
        self.StartButton.setEnabled(False)
        icon4 = QtGui.QIcon()
        icon4.addPixmap(QtGui.QPixmap(":/res/ImgCheck.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.StartButton.setIcon(icon4)
        self.StartButton.setObjectName("StartButton")
        self.horizontalLayout_3.addWidget(self.StartButton)
        self.horizontalLayout_4.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_4.setStretch(0, 4)
        self.horizontalLayout_4.setStretch(1, 5)
        self.verticalLayout.addLayout(self.horizontalLayout_4)
        self.verticalLayout.setStretch(0, 20)
        self.verticalLayout.setStretch(1, 1)
        self.TabWidget.addTab(self.TabHotUpdate, "")
        self.TabCompile = QtWidgets.QWidget()
        self.TabCompile.setObjectName("TabCompile")
        self.TabWidget.addTab(self.TabCompile, "")
        self.verticalLayout_2.addWidget(self.TabWidget)
        self.ProgressBar = QtWidgets.QProgressBar(ToolForm)
        self.ProgressBar.setTextVisible(False)
        self.ProgressBar.setObjectName("ProgressBar")
        self.verticalLayout_2.addWidget(self.ProgressBar)

        self.retranslateUi(ToolForm)
        self.TabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(ToolForm)

    def retranslateUi(self, ToolForm):
        _translate = QtCore.QCoreApplication.translate
        ToolForm.setWindowTitle(_translate("ToolForm", "工具"))
        self.UploadGroupBox.setTitle(_translate("ToolForm", "上传配置"))
        self.NoUploadCheckBox.setText(_translate("ToolForm", "不上传文件"))
        self.UploadDiffHashCheckBox.setText(_translate("ToolForm", "仅上传哈希值不同的文件"))
        self.UploadZipCheckBox.setText(_translate("ToolForm", "所有文件压缩后上传（将\n"
"需要接收端解压）"))
        self.FtpAccountLineEdit.setPlaceholderText(_translate("ToolForm", "FTP账号"))
        self.FtpPasswordLineEdit.setPlaceholderText(_translate("ToolForm", "FTP密码"))
        self.VersionGroupBox.setTitle(_translate("ToolForm", "版本配置"))
        self.V1RadioButton.setText(_translate("ToolForm", "版本不变"))
        self.V3RadioButton.setText(_translate("ToolForm", "使用本地版本+1"))
        self.V4RadioButton.setText(_translate("ToolForm", "使用指定版本："))
        self.V2RadioButton.setText(_translate("ToolForm", "使用远程版本+1"))
        self.DownloadGroupBox.setTitle(_translate("ToolForm", "下载配置"))
        self.label.setText(_translate("ToolForm", "要下载的文件满足以下条件\n"
"\n"
"         时，将直接下载整\n"
"\n"
"个zip文件："))
        self.NumFilterCheckBox.setText(_translate("ToolForm", "数量大于"))
        self.NumFilterSpinBox.setSuffix(_translate("ToolForm", "个"))
        self.SizeFilterCheckBox.setText(_translate("ToolForm", "容量大于"))
        self.SizeFilterSpinBox.setSuffix(_translate("ToolForm", "兆"))
        self.OtherSettingGroupBox.setTitle(_translate("ToolForm", "其他配置"))
        self.UniqueConfigCheckBox.setText(_translate("ToolForm", "所有模块使用统一配置"))
        self.SaveOnExitCheckBox.setText(_translate("ToolForm", "退出时保存配置"))
        self.GenerateGroupBox.setTitle(_translate("ToolForm", "生成配置"))
        self.UncomperssZipCheckBox.setText(_translate("ToolForm", "将zip文件标识为需要解压"))
        self.CompressResCheckBox.setText(_translate("ToolForm", "对资源加密[lua/luac/png]"))
        self.CompressPasswordLineEdit.setPlaceholderText(_translate("ToolForm", "密码"))
        self.CompressImgCheckBox.setText(_translate("ToolForm", "压缩图像[png]并指定质量"))
        self.MinQualitySpinBox.setPrefix(_translate("ToolForm", "最低"))
        self.MaxQualitySpinBox.setPrefix(_translate("ToolForm", "最高"))
        self.CompileLuaCheckBox.setText(_translate("ToolForm", "编译lua文件"))
        self.SelectAllButton.setText(_translate("ToolForm", "全选模块"))
        self.SelectOtherButton.setText(_translate("ToolForm", "反选模块"))
        self.ManageModuleButton.setText(_translate("ToolForm", "管理模块"))
        self.StartTimerCheckBox.setText(_translate("ToolForm", "定时："))
        self.StartTimerSpinBox.setSuffix(_translate("ToolForm", "秒"))
        self.StartButton.setText(_translate("ToolForm", "开始"))
        self.TabWidget.setTabText(self.TabWidget.indexOf(self.TabHotUpdate), _translate("ToolForm", "热更"))
        self.TabWidget.setTabText(self.TabWidget.indexOf(self.TabCompile), _translate("ToolForm", "编译"))
import UI_rc
