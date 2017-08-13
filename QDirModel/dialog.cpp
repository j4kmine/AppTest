#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // Create and populate our model
        model = new QDirModel(this);

        // Enable modifying file system
        model->setReadOnly(false);
        // Setup sort criteria
        // directory first, ignore case,
        // and sort by name
        model->setSorting(QDir::DirsFirst |
                          QDir::IgnoreCase |
                          QDir::Name);
        // Tie TreeView with DirModel
        // QTreeView::setModel(QAbstractItemModel * model)
        // Reimplemented from QAbstractItemView::setModel().
        ui->treeView->setModel(model);
        // Set initial selection
            QModelIndex index = model->index("C:/");

            // Set initial view of directory
            // for the selected drive as expanded
            ui->treeView->expand(index);

            // Make it scroll to the selected
            ui->treeView->scrollTo(index);

            // Highlight the selected
            ui->treeView->setCurrentIndex(index);

            // Resizing the column - first column
            ui->treeView->resizeColumnToContents(0);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    //make dir
    // Make directory
        QModelIndex index = ui->treeView->currentIndex();
        if(!index.isValid()) return;

        QString name  = QInputDialog::getText(this, "Name", "Enter a name");

        if(name.isEmpty()) return;

        model->mkdir(index, name);
}

void Dialog::on_pushButton_2_clicked()
{
    //delete dir
    // Get the current selection
        QModelIndex index = ui->treeView->currentIndex();
        if(!index.isValid()) return;

        if(model->fileInfo(index).isDir())
        {
            // directory
            model->rmdir(index);
        }
        else
        {
            // file
            model->remove(index);
        }
}
