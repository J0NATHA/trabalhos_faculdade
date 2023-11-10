package com.example.aula20230926

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface ProdutoDao {

    @Query("SELECT * FROM produto_table ORDER BY nome ASC")
    fun getProdutos(): Flow<List<Produto>>

    @Insert(onConflict = OnConflictStrategy.IGNORE)
    suspend fun inserir(produto: Produto)

    @Delete
    suspend fun excluir(produto: Produto)

    @Query("DELETE FROM produto_table WHERE idProduto = :id")
    fun deleteById(id: Int)
}