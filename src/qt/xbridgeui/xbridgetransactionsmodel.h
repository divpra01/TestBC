//******************************************************************************
//******************************************************************************

#ifndef XBRIDGETRANSACTIONSMODEL_H
#define XBRIDGETRANSACTIONSMODEL_H

#include "uint256.h"
#include "xbridge/xbridgetransactiondescr.h"
#include "xbridge/xbridgedef.h"

#include <QAbstractTableModel>
#include <QStringList>
#include <QTimer>

#include <vector>
#include <string>
#include <boost/cstdint.hpp>

//******************************************************************************
//******************************************************************************
class XBridgeTransactionsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    XBridgeTransactionsModel();
    ~XBridgeTransactionsModel();

    enum ColumnIndex
    {
        Total       = 0,
        FirstColumn = Total,
        Size        = 1,
        BID         = 2,
        State       = 3,
        LastColumn  = State
    };

    static const int rawStateRole = Qt::UserRole + 1;

public:
    virtual int      rowCount(const QModelIndex &) const;
    virtual int      columnCount(const QModelIndex &) const;
    virtual QVariant data(const QModelIndex & idx, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool isMyTransaction(const unsigned int index) const;

    bool newTransaction(const std::string & from,
                        const std::string & to,
                        const std::string & fromCurrency,
                        const std::string & toCurrency,
                        const double fromAmount,
                        const double toAmount);
    bool newTransactionFromPending(const uint256 & id,
                                   const std::vector<unsigned char> & hub,
                                   const std::string & from,
                                   const std::string & to);

    bool cancelTransaction(const uint256 & id);
    bool rollbackTransaction(const uint256 & id);

    xbridge::TransactionDescrPtr item(const unsigned int index) const;

private slots:
    void onTimer();

private:
    void onTransactionReceived(const xbridge::TransactionDescrPtr & tx);
    void onTransactionStateChanged(const uint256 & id);

    QString transactionState(const xbridge::TransactionDescr::State state) const;

private:
    QStringList m_columns;

    std::vector<xbridge::TransactionDescrPtr> m_transactions;

    QTimer m_timer;
};

#endif // XBRIDGETRANSACTIONSMODEL_H
