# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'UI/ModuleMgrDlg.ui'
#
# Created by: PyQt5 UI code generator 5.15.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_ModuleMgrDlg(object):
    def setupUi(self, ModuleMgrDlg):
        ModuleMgrDlg.setObjectName("ModuleMgrDlg")
        ModuleMgrDlg.setWindowModality(QtCore.Qt.WindowModal)
        ModuleMgrDlg.resize(600, 300)
        ModuleMgrDlg.setMinimumSize(QtCore.QSize(300, 150))
        ModuleMgrDlg.setMaximumSize(QtCore.QSize(600, 300))
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/res/IcoModule.ico"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        ModuleMgrDlg.setWindowIcon(icon)
        ModuleMgrDlg.setModal(True)
        self.horizontalLayout = QtWidgets.QHBoxLayout(ModuleMgrDlg)
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout.setSpacing(2)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.gridLayout = QtWidgets.QGridLayout()
        self.gridLayout.setSpacing(2)
        self.gridLayout.setObjectName("gridLayout")
        self.NewModuleButton = QtWidgets.QPushButton(ModuleMgrDlg)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/res/ImgPlus.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.NewModuleButton.setIcon(icon1)
        self.NewModuleButton.setAutoDefault(False)
        self.NewModuleButton.setObjectName("NewModuleButton")
        self.gridLayout.addWidget(self.NewModuleButton, 1, 0, 1, 1)
        self.DelModuleButton = QtWidgets.QPushButton(ModuleMgrDlg)
        self.DelModuleButton.setEnabled(False)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/res/ImgDel.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.DelModuleButton.setIcon(icon2)
        self.DelModuleButton.setAutoDefault(False)
        self.DelModuleButton.setObjectName("DelModuleButton")
        self.gridLayout.addWidget(self.DelModuleButton, 1, 1, 1, 1)
        self.ModuleListWidget = QtWidgets.QListWidget(ModuleMgrDlg)
        self.ModuleListWidget.setObjectName("ModuleListWidget")
        self.gridLayout.addWidget(self.ModuleListWidget, 0, 0, 1, 2)
        self.horizontalLayout.addLayout(self.gridLayout)
        self.ModuleInfoTabWidget = QtWidgets.QTabWidget(ModuleMgrDlg)
        self.ModuleInfoTabWidget.setEnabled(False)
        self.ModuleInfoTabWidget.setObjectName("ModuleInfoTabWidget")
        self.tab = QtWidgets.QWidget()
        self.tab.setObjectName("tab")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.tab)
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_2.setSpacing(0)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.InfoTableWidget = QtWidgets.QTableWidget(self.tab)
        self.InfoTableWidget.setSelectionMode(QtWidgets.QAbstractItemView.SingleSelection)
        self.InfoTableWidget.setGridStyle(QtCore.Qt.SolidLine)
        self.InfoTableWidget.setObjectName("InfoTableWidget")
        self.InfoTableWidget.setColumnCount(1)
        self.InfoTableWidget.setRowCount(4)
        item = QtWidgets.QTableWidgetItem()
        self.InfoTableWidget.setVerticalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.InfoTableWidget.setVerticalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        self.InfoTableWidget.setVerticalHeaderItem(2, item)
        item = QtWidgets.QTableWidgetItem()
        self.InfoTableWidget.setVerticalHeaderItem(3, item)
        item = QtWidgets.QTableWidgetItem()
        self.InfoTableWidget.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.InfoTableWidget.setItem(0, 0, item)
        item = QtWidgets.QTableWidgetItem()
        self.InfoTableWidget.setItem(1, 0, item)
        item = QtWidgets.QTableWidgetItem()
        self.InfoTableWidget.setItem(2, 0, item)
        item = QtWidgets.QTableWidgetItem()
        self.InfoTableWidget.setItem(3, 0, item)
        self.InfoTableWidget.horizontalHeader().setVisible(False)
        self.InfoTableWidget.horizontalHeader().setStretchLastSection(True)
        self.InfoTableWidget.verticalHeader().setDefaultSectionSize(20)
        self.InfoTableWidget.verticalHeader().setHighlightSections(False)
        self.gridLayout_2.addWidget(self.InfoTableWidget, 0, 0, 1, 1)
        self.ModuleInfoTabWidget.addTab(self.tab, "")
        self.tab_2 = QtWidgets.QWidget()
        self.tab_2.setObjectName("tab_2")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.tab_2)
        self.gridLayout_3.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_3.setSpacing(0)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.DelDirButton = QtWidgets.QPushButton(self.tab_2)
        self.DelDirButton.setEnabled(False)
        self.DelDirButton.setIcon(icon2)
        self.DelDirButton.setObjectName("DelDirButton")
        self.gridLayout_3.addWidget(self.DelDirButton, 1, 2, 1, 1)
        self.NewDirButton = QtWidgets.QPushButton(self.tab_2)
        self.NewDirButton.setIcon(icon1)
        self.NewDirButton.setObjectName("NewDirButton")
        self.gridLayout_3.addWidget(self.NewDirButton, 1, 1, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_3.addItem(spacerItem, 1, 0, 1, 1)
        self.DirsListWidget = QtWidgets.QListWidget(self.tab_2)
        self.DirsListWidget.setObjectName("DirsListWidget")
        self.gridLayout_3.addWidget(self.DirsListWidget, 0, 0, 1, 3)
        self.ModuleInfoTabWidget.addTab(self.tab_2, "")
        self.tab_3 = QtWidgets.QWidget()
        self.tab_3.setObjectName("tab_3")
        self.gridLayout_4 = QtWidgets.QGridLayout(self.tab_3)
        self.gridLayout_4.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_4.setSpacing(0)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.DelFileButton = QtWidgets.QPushButton(self.tab_3)
        self.DelFileButton.setEnabled(False)
        self.DelFileButton.setIcon(icon2)
        self.DelFileButton.setObjectName("DelFileButton")
        self.gridLayout_4.addWidget(self.DelFileButton, 1, 2, 1, 1)
        self.NewFileButton = QtWidgets.QPushButton(self.tab_3)
        self.NewFileButton.setIcon(icon1)
        self.NewFileButton.setObjectName("NewFileButton")
        self.gridLayout_4.addWidget(self.NewFileButton, 1, 1, 1, 1)
        spacerItem1 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_4.addItem(spacerItem1, 1, 0, 1, 1)
        self.FilesListWidget = QtWidgets.QListWidget(self.tab_3)
        self.FilesListWidget.setObjectName("FilesListWidget")
        self.gridLayout_4.addWidget(self.FilesListWidget, 0, 0, 1, 3)
        self.ModuleInfoTabWidget.addTab(self.tab_3, "")
        self.horizontalLayout.addWidget(self.ModuleInfoTabWidget)
        self.horizontalLayout.setStretch(0, 4)
        self.horizontalLayout.setStretch(1, 12)

        self.retranslateUi(ModuleMgrDlg)
        self.ModuleInfoTabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(ModuleMgrDlg)

    def retranslateUi(self, ModuleMgrDlg):
        _translate = QtCore.QCoreApplication.translate
        ModuleMgrDlg.setWindowTitle(_translate("ModuleMgrDlg", "模块管理"))
        self.NewModuleButton.setText(_translate("ModuleMgrDlg", "新增模块"))
        self.DelModuleButton.setText(_translate("ModuleMgrDlg", "删除模块"))
        item = self.InfoTableWidget.verticalHeaderItem(0)
        item.setText(_translate("ModuleMgrDlg", "downloadUrl"))
        item.setToolTip(_translate("ModuleMgrDlg", "远程文件根目录"))
        item = self.InfoTableWidget.verticalHeaderItem(1)
        item.setText(_translate("ModuleMgrDlg", "uploadUrl"))
        item.setToolTip(_translate("ModuleMgrDlg", "上传根路径"))
        item = self.InfoTableWidget.verticalHeaderItem(2)
        item.setText(_translate("ModuleMgrDlg", "remoteVersionUrl"))
        item.setToolTip(_translate("ModuleMgrDlg", "远程版本文件"))
        item = self.InfoTableWidget.verticalHeaderItem(3)
        item.setText(_translate("ModuleMgrDlg", "remoteManifestUrl"))
        item.setToolTip(_translate("ModuleMgrDlg", "远程清单文件"))
        item = self.InfoTableWidget.horizontalHeaderItem(0)
        item.setText(_translate("ModuleMgrDlg", "值"))
        __sortingEnabled = self.InfoTableWidget.isSortingEnabled()
        self.InfoTableWidget.setSortingEnabled(False)
        self.InfoTableWidget.setSortingEnabled(__sortingEnabled)
        self.ModuleInfoTabWidget.setTabText(self.ModuleInfoTabWidget.indexOf(self.tab), _translate("ModuleMgrDlg", "常规"))
        self.DelDirButton.setText(_translate("ModuleMgrDlg", "删除目录"))
        self.NewDirButton.setText(_translate("ModuleMgrDlg", "新增目录"))
        self.ModuleInfoTabWidget.setTabText(self.ModuleInfoTabWidget.indexOf(self.tab_2), _translate("ModuleMgrDlg", "目录"))
        self.DelFileButton.setText(_translate("ModuleMgrDlg", "删除文件"))
        self.NewFileButton.setText(_translate("ModuleMgrDlg", "新增文件"))
        self.ModuleInfoTabWidget.setTabText(self.ModuleInfoTabWidget.indexOf(self.tab_3), _translate("ModuleMgrDlg", "文件"))
import UI_rc