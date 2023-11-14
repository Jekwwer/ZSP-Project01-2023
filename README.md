<h1>Simple I/O Programs Implementation</h1>

<blockquote>
  <p>
    🎓 <strong>University</strong>:
    <a href="https://en.vspj.cz/school/welcome">VŠPJ</a>
  </p>

  <p>
    📚 <strong>Subject</strong>:
    <a
      href="https://www.vspj.cz/eprihlaska/rozcestnik/detail-oboru/obor/aplikovana-informatika/tab/studijni-plany/plan/66/predmet/500067#tabs"
      >Fundamentals of Structural Programming (ZSP)</a
    >
  </p>

  <p>📅<strong>Academic Year</strong>: 2023/24</p>
</blockquote>

<hr />

<h2>📋 <strong>Assignment Overview</strong></h2>

<hr />

<h3>
  📌 <strong>Task 1</strong>: Calculate the Purchase Price for Purchased Goods
  (Function:
  <a
    href="https://github.com/Jekwwer/ZSP-Homework01-2023/blob/bd06198be6283c0e97a7924f60b702b1e01a2b22/src/functions.cpp#L78"
    ><code>u1_1</code></a
  >)
</h3>

<p>
  <strong>Description</strong>: <br />
  Upon entering the number of pieces and the unit price (excluding VAT) via
  keyboard, the program will compute:
</p>

<ul>
  <li>Unit price inclusive of VAT (rounded as per mathematical rules).</li>
  <li>Total price excluding VAT.</li>
  <li>Aggregate price inclusive of VAT (rounded as per mathematical rules).</li>
</ul>

<p>
  <strong>Sample Output:</strong><br />
  <code>
    Účtenka<br />
    Cena bez DPH/ks 200 Kč&lt;tab&gt;Cena s DPH/ks 240 Kč<br />
    Počet kusů: 5&lt;tab&gt;Cena bez DPH 1000 Kč&lt;tab&gt;Cena s DPH (20 %)
    1400 Kč
  </code>
</p>

<p>
  <strong>Translated Sample Output</strong>:<br />
  <code>
    Receipt<br />
    Price without VAT/pc 200 CZK&lt;tab&gt;Price with VAT/pc 240 CZK<br />
    Number of pieces: 5&lt;tab&gt;Price without VAT 1000 CZK&lt;tab&gt;Price
    with VAT (20%) 1400 CZK
  </code>
</p>

<hr />

<h3>
  📌 <strong>Task 2</strong>: Calculate Report Card Grades (Function:
  <a
    href="https://github.com/Jekwwer/ZSP-Homework01-2023/blob/bd06198be6283c0e97a7924f60b702b1e01a2b22/src/functions.cpp#L132"
    ><code>u1_2</code></a
  >)
</h3>

<p>
  <strong>Description</strong>: <br />
  Upon entering 5 grades via keyboard, the program will determine the average of
  the grades and categorize the grade as either: pass with distinction, pass, or
  fail.
</p>

<p>
  <strong>Note</strong>: <br />
  Implement a suitable constant variable and define its value within the
  program.
</p>

<p>
  <strong>Sample Output</strong>:<br />
  <code>
    Známky: z1&lt;tab&gt;z2&lt;z3&gt;&lt;tab&gt;z4&lt;tab&gt;z5<br />
    [Průměrná hodnota zaokrouhlená na dvě desetinná místa]<br />
    Prospěl s vyznamenáním: {1:Ano/0:Ne}<br />
    Prospěl: {1:Ano/0:Ne}<br />
    Neprospěl: {1:Ano/0:Ne}
  </code>
</p>

<p>
  <strong>Translated Sample Output</strong>:<br />
  <code>
    Marks: z1&lt;tab&gt;z2&lt;z3&gt;&lt;tab&gt;z4&lt;tab&gt;z5<br />
    [Average value rounded to two decimal places]<br />
    Pass with distinction: {1:Yes/0:No}<br />
    Passed: {1:Yes/0:No}<br />
    Fail: {1:Yes/0:No}
  </code>
</p>

<hr />

<h3>
  📌 <strong>Task 3</strong>: Currency Exchange Program (Function:
  <a
    href="https://github.com/Jekwwer/ZSP-Homework01-2023/blob/bd06198be6283c0e97a7924f60b702b1e01a2b22/src/functions.cpp#L219"
    ><code>u1_3</code></a
  >)
</h3>

<p>
  <strong>Description</strong>: <br />
  Users will input a currency code (e.g., EUR, GBL, etc.) and the equivalent
  value of that currency in CZK. Subsequently, the number of currency units to
  be exchanged will be input. The program will then calculate and display the
  total cost in CZK for the foreign currency exchanged.
</p>

<p>
  <strong>Sample Output:</strong><br />
  <code>
    1 GBP = 24.9 Kč<br />
    Nákup: 5 GBP<br />
    Celkem: 5 x 24.9 = 124.5 Kč Zaokrouhleno: 125 Kč
  </code>
</p>

<p><strong>Translated Sample Output</strong>:</p>

<p>
  <code>
    1 GBP = 24.9 CZK<br />
    Purchase: 5 GBP<br />
    Total: 5 x 24.9 = 124.5 CZK Rounded: 125 CZK
  </code>
</p>

<hr />

<h2>📊 <strong>Evaluation Results</strong></h2>

<table>
  <tr>
    <th>Note</th>
    <th>Status</th>
    <th style="text-align: right"></th>
  </tr>
  <tr>
    <td>U1_1 OK</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>U1_2 OK</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>U1_3 OK</td>
    <td></td>
    <td></td>
  </tr>
  <tr>
    <td>
      User-unfriendly,<br />lacks instructions on what the user should do.<br />(-1
      point)
    </td>
    <td>
      Specs lacked explicit requirements.<br />Evaluator credited +1 point
      back.<br />(+1 point)
    </td>
    <td></td>
  </tr>
  <tr>
    <td><strong>Total Points:</strong></td>
    <td></td>
    <td style="text-align: right"><strong>12/12</strong></td>
  </tr>
  <tr>
    <td></td>
    <td></td>
    <td style="text-align: right">🟢🟢🟢🟢🟢</td>
  </tr>
</table>
