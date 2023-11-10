package com.example.aula20230926

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "produto_table")
class Produto {
    @PrimaryKey(autoGenerate = true)
    var idProduto: Int = 0
    var nome = ""
    var quantidade = 0
}