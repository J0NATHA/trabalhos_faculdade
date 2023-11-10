package com.example.aula20230926

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.lifecycle.asLiveData
import androidx.lifecycle.viewModelScope
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Dispatchers.IO
import kotlinx.coroutines.flow.onCompletion
import kotlinx.coroutines.launch


class ProdutoActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_produto)

        val recyclerView = findViewById<RecyclerView>(R.id.lstProdutos)
        val adapter = ProdutoListAdapter()
        recyclerView.adapter = adapter
        recyclerView.layoutManager = LinearLayoutManager(this)
        CoroutineScope(Dispatchers.IO).launch{
            var p = Produto()
            p.nome = "Teste"
            p.quantidade = 1000
            (application as WordsApplication).database.produtoDao().inserir(p)
        }

        (application as WordsApplication).database.produtoDao().getProdutos().asLiveData().observe(this) {
            it -> adapter.submitList(it)
        }

    }
}