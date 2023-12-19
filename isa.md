
<dt>Separate the instruction into parts</dt>
<dd><p>Treat the instruction as having four parts:</p>
<table>
<colgroup>



</colgroup>
<thead>
<tr class="header">
<th style="text-align: left;">bits</th>
<th style="text-align: left;">name</th>
<th style="text-align: left;">meaning</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td style="text-align: left;">7</td>
<td style="text-align: left;">reserved</td>
<td style="text-align: left;">If set, an invalid instruction. Do not do work or advance the PC if this bit is 1.</td>
</tr>
<tr class="even">
<td style="text-align: left;">[4,&nbsp;7)</td>
<td style="text-align: left;"><code>opcode</code></td>
<td style="text-align: left;">Specifies what action to take</td>
</tr>
<tr class="odd">
<td style="text-align: left;">[2,&nbsp;4)</td>
<td style="text-align: left;"><code>a</code></td>
<td style="text-align: left;">The index of a register</td>
</tr>
<tr class="even">
<td style="text-align: left;">[0,&nbsp;2)</td>
<td style="text-align: left;"><code>b</code></td>
<td style="text-align: left;">The index of another register, or details about opcode</td>
</tr>
</tbody>
</table>
</dd>
<dt>Execute the instruction</dt>
<dd>

<ul>
<li><p>If <code>reserved</code> is 1, set the next PC to the current PC instead of advancing it and do nothing else.</p></li>
<li><p>Otherwise, see the following table, where <code>rA</code> means <q>the value stored in register number <code>a</code></q> and <code>rB</code> means <q>the value stored in register number <code>b</code>.</q> Unless a different value of the <code>pc</code> is specified in the table, also add one to the <code>pc</code> for each instruction.</p></li>
</ul>
<table>
<colgroup>


</colgroup>
<thead>
<tr class="header">
<th style="text-align: center;"><code>opcode</code></th>
<th style="text-align: left;">Behavior</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td style="text-align: center;">0</td>
<td style="text-align: left;"><code>rA = rB</code></td>
</tr>
<tr class="even">
<td style="text-align: center;">1</td>
<td style="text-align: left;"><code>rA += rB</code></td>
</tr>
<tr class="odd">
<td style="text-align: center;">2</td>
<td style="text-align: left;"><code>rA &amp;= rB</code></td>
</tr>
<tr class="even">
<td style="text-align: center;">3</td>
<td style="text-align: left;"><code>rA =</code> read from memory at address <code>rB</code></td>
</tr>
<tr class="odd">
<td style="text-align: center;">4</td>
<td style="text-align: left;">write <code>rA</code> to memory at address <code>rB</code></td>
</tr>
<tr class="even">
<td style="text-align: center;">5</td>
<td style="text-align: left;"><p>do different things for different values of <code>b</code>:</p>
<table>
<colgroup>


</colgroup>
<thead>
<tr class="header">
<th style="text-align: center;"><code>b</code></th>
<th style="text-align: left;">action</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td style="text-align: center;">0</td>
<td style="text-align: left;"><code>rA = ~rA</code></td>
</tr>
<tr class="even">
<td style="text-align: center;">1</td>
<td style="text-align: left;"><code>rA = -rA</code></td>
</tr>
<tr class="odd">
<td style="text-align: center;">2</td>
<td style="text-align: left;"><code>rA = !rA</code></td>
</tr>
<tr class="even">
<td style="text-align: center;">3</td>
<td style="text-align: left;"><code>rA = pc</code></td>
</tr>
</tbody>
</table></td>
</tr>
<tr class="odd">
<td style="text-align: center;">6</td>
<td style="text-align: left;"><p>do different things for different values of <code>b</code>:</p>
<table>
<colgroup>


</colgroup>
<thead>
<tr class="header">
<th style="text-align: center;"><code>b</code></th>
<th style="text-align: left;">action</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td style="text-align: center;">0</td>
<td style="text-align: left;"><code>rA =</code> read from memory at <code>pc + 1</code></td>
</tr>
<tr class="even">
<td style="text-align: center;">1</td>
<td style="text-align: left;"><code>rA +=</code> read from memory at <code>pc + 1</code></td>
</tr>
<tr class="odd">
<td style="text-align: center;">2</td>
<td style="text-align: left;"><code>rA &amp;=</code> read from memory at <code>pc + 1</code></td>
</tr>
<tr class="even">
<td style="text-align: center;">3</td>
<td style="text-align: left;"><code>rA =</code> read from memory at the address stored at <code>pc + 1</code></td>
</tr>
</tbody>
</table>
<p>In all 4 cases, increase <code>pc</code> by 2, not 1, at the end of this instruction</p></td>
</tr>
<tr class="even">
<td style="text-align: center;">7</td>
<td style="text-align: left;">Compare <code>rA</code> (as an 8-bit 2’s-complement number) to <code>0</code>; if <code>rA &lt;= 0</code>, set <code>pc = rB</code> otherwise, increment <code>pc</code> like normal.</td>
</tr>
</tbody>
</table>
</dd>
</dl>
</div>