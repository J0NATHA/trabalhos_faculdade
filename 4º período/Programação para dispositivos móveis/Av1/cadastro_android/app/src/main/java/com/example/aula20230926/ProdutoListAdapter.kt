package com.example.aula20230926

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView

class ProdutoListAdapter : ListAdapter<Produto, ProdutoListAdapter.ProdutoViewHolder>(ProdutosComparator()) {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ProdutoViewHolder {
        return ProdutoViewHolder.create(parent)
    }

    override fun onBindViewHolder(holder: ProdutoViewHolder, position: Int) {
        val current = getItem(position)
        holder.bind(current)
    }

    class ProdutoViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        private val txtIdNome: TextView = itemView.findViewById(R.id.txtIdNome)
        private val txtQuantidade: TextView = itemView.findViewById(R.id.txtQuantidade)

        fun bind(produto: Produto) {
            txtIdNome.text = "${produto.idProduto}: ${produto.nome}"
            txtQuantidade.text = "Qtd: ${produto.quantidade}"
        }

        companion object {
            fun create(parent: ViewGroup): ProdutoViewHolder {
                val view: View = LayoutInflater.from(parent.context)
                    .inflate(R.layout.linha_produto, parent, false)
                return ProdutoViewHolder(view)
            }
        }
    }

    class ProdutosComparator : DiffUtil.ItemCallback<Produto>() {
        override fun areItemsTheSame(oldItem: Produto, newItem: Produto): Boolean {
            return oldItem === newItem
        }

        override fun areContentsTheSame(oldItem: Produto, newItem: Produto): Boolean {
            return oldItem.idProduto == newItem.idProduto
        }
    }
}